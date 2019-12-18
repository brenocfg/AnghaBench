#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_3__ {int mapaddr; int ioaddr; scalar_t__ current_space; int last_iodbex; int flags; size_t last_iosize; } ;
typedef  TYPE_1__ pcc_socket_t ;

/* Variables and functions */
 int KSEG1 ; 
 int MAP_16BIT ; 
 int /*<<< orphan*/  PCADR ; 
 int /*<<< orphan*/  PCCR ; 
 int /*<<< orphan*/  PCIRC ; 
 int PCIRC_BWERR ; 
 int /*<<< orphan*/  PCMOD ; 
 int PCMOD_AS_IO ; 
 int PCMOD_CBSZ ; 
 int PCMOD_DBEX ; 
 scalar_t__ as_attr ; 
 scalar_t__ as_io ; 
 void* dummy_readbuf ; 
 int pcc_get (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_lock ; 
 int /*<<< orphan*/  pcc_set (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,size_t) ; 
 void* readb (int) ; 
 void* readw (int) ; 
 TYPE_1__* socket ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writew (unsigned short,int) ; 

void pcc_iorw(int sock, unsigned long port, void *buf, size_t size, size_t nmemb, int wr, int flag)
{
	u_long addr;
	u_long flags;
	int need_ex;
#ifdef PCC_DEBUG_DBEX
	int _dbex;
#endif
	pcc_socket_t *t = &socket[sock];
#ifdef CHAOS_PCC_DEBUG
	int map_changed = 0;
#endif

	/* Need lock ? */
	spin_lock_irqsave(&pcc_lock, flags);

	/*
	 * Check if need dbex
	 */
	need_ex = (size > 1 && flag == 0) ? PCMOD_DBEX : 0;
#ifdef PCC_DEBUG_DBEX
	_dbex = need_ex;
	need_ex = 0;
#endif

	/*
	 * calculate access address
	 */
	addr = t->mapaddr + port - t->ioaddr + KSEG1; /* XXX */

	/*
	 * Check current mapping
	 */
	if (t->current_space != as_io || t->last_iodbex != need_ex) {

		u_long cbsz;

		/*
		 * Disable first
		 */
		pcc_set(sock, PCCR, 0);

		/*
		 * Set mode and io address
		 */
		cbsz = (t->flags & MAP_16BIT) ? 0 : PCMOD_CBSZ;
		pcc_set(sock, PCMOD, PCMOD_AS_IO | cbsz | need_ex);
		pcc_set(sock, PCADR, addr & 0x1ff00000);

		/*
		 * Enable and read it
		 */
		pcc_set(sock, PCCR, 1);

#ifdef CHAOS_PCC_DEBUG
#if 0
		map_changed = (t->current_space == as_attr && size == 2); /* XXX */
#else
		map_changed = 1;
#endif
#endif
		t->current_space = as_io;
	}

	/*
	 * access to IO space
	 */
	if (size == 1) {
		/* Byte */
		unsigned char *bp = (unsigned char *)buf;

#ifdef CHAOS_DEBUG
		if (map_changed) {
			dummy_readbuf = readb(addr);
		}
#endif
		if (wr) {
			/* write Byte */
			while (nmemb--) {
				writeb(*bp++, addr);
			}
		} else {
			/* read Byte */
			while (nmemb--) {
	    		*bp++ = readb(addr);
			}
		}
	} else {
		/* Word */
		unsigned short *bp = (unsigned short *)buf;

#ifdef CHAOS_PCC_DEBUG
		if (map_changed) {
			dummy_readbuf = readw(addr);
		}
#endif
		if (wr) {
			/* write Word */
			while (nmemb--) {
#ifdef PCC_DEBUG_DBEX
				if (_dbex) {
					unsigned char *cp = (unsigned char *)bp;
					unsigned short tmp;
					tmp = cp[1] << 8 | cp[0];
					writew(tmp, addr);
					bp++;
				} else
#endif
				writew(*bp++, addr);
	    	}
	    } else {
	    	/* read Word */
	    	while (nmemb--) {
#ifdef  PCC_DEBUG_DBEX
				if (_dbex) {
					unsigned char *cp = (unsigned char *)bp;
					unsigned short tmp;
					tmp = readw(addr);
					cp[0] = tmp & 0xff;
					cp[1] = (tmp >> 8) & 0xff;
					bp++;
				} else
#endif
				*bp++ = readw(addr);
	    	}
	    }
	}

#if 1
	/* addr is no longer used */
	if ((addr = pcc_get(sock, PCIRC)) & PCIRC_BWERR) {
	  printk("m32r_pcc: BWERR detected : port 0x%04lx : iosize %dbit\n",
			 port, size * 8);
	  pcc_set(sock, PCIRC, addr);
	}
#endif
	/*
	 * save state
	 */
	t->last_iosize = size;
	t->last_iodbex = need_ex;

	/* Need lock ? */

	spin_unlock_irqrestore(&pcc_lock,flags);

	return;
}