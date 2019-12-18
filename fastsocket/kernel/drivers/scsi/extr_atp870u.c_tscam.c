#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct atp_unit {int* ioport; int scam_on; unsigned short* host_id; int chip_ver; } ;
struct Scsi_Host {int /*<<< orphan*/  hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned char fun_scam (struct atp_unit*,unsigned short*) ; 
 int inb (unsigned int) ; 
 int inw (unsigned int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outw (unsigned short,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tscam(struct Scsi_Host *host)
{

	unsigned int tmport;
	unsigned char i, j, k;
	unsigned long n;
	unsigned short int m, assignid_map, val;
	unsigned char mbuf[33], quintet[2];
	struct atp_unit *dev = (struct atp_unit *)&host->hostdata;
	static unsigned char g2q_tab[8] = {
		0x38, 0x31, 0x32, 0x2b, 0x34, 0x2d, 0x2e, 0x27
	};

/*  I can't believe we need this before we've even done anything.  Remove it
 *  and see if anyone bitches.
	for (i = 0; i < 0x10; i++) {
		udelay(0xffff);
	}
 */

	tmport = dev->ioport[0] + 1;
	outb(0x08, tmport++);
	outb(0x7f, tmport);
	tmport = dev->ioport[0] + 0x11;
	outb(0x20, tmport);

	if ((dev->scam_on & 0x40) == 0) {
		return;
	}
	m = 1;
	m <<= dev->host_id[0];
	j = 16;
	if (dev->chip_ver < 4) {
		m |= 0xff00;
		j = 8;
	}
	assignid_map = m;
	tmport = dev->ioport[0] + 0x02;
	outb(0x02, tmport++);	/* 2*2=4ms,3EH 2/32*3E=3.9ms */
	outb(0, tmport++);
	outb(0, tmport++);
	outb(0, tmport++);
	outb(0, tmport++);
	outb(0, tmport++);
	outb(0, tmport++);

	for (i = 0; i < j; i++) {
		m = 1;
		m = m << i;
		if ((m & assignid_map) != 0) {
			continue;
		}
		tmport = dev->ioport[0] + 0x0f;
		outb(0, tmport++);
		tmport += 0x02;
		outb(0, tmport++);
		outb(0, tmport++);
		outb(0, tmport++);
		if (i > 7) {
			k = (i & 0x07) | 0x40;
		} else {
			k = i;
		}
		outb(k, tmport++);
		tmport = dev->ioport[0] + 0x1b;
		if (dev->chip_ver == 4) {
			outb(0x01, tmport);
		} else {
			outb(0x00, tmport);
		}
wait_rdyok:
		tmport = dev->ioport[0] + 0x18;
		outb(0x09, tmport);
		tmport += 0x07;

		while ((inb(tmport) & 0x80) == 0x00)
			cpu_relax();
		tmport -= 0x08;
		k = inb(tmport);
		if (k != 0x16) {
			if ((k == 0x85) || (k == 0x42)) {
				continue;
			}
			tmport = dev->ioport[0] + 0x10;
			outb(0x41, tmport);
			goto wait_rdyok;
		}
		assignid_map |= m;

	}
	tmport = dev->ioport[0] + 0x02;
	outb(0x7f, tmport);
	tmport = dev->ioport[0] + 0x1b;
	outb(0x02, tmport);

	outb(0, 0x80);

	val = 0x0080;		/* bsy  */
	tmport = dev->ioport[0] + 0x1c;
	outw(val, tmport);
	val |= 0x0040;		/* sel  */
	outw(val, tmport);
	val |= 0x0004;		/* msg  */
	outw(val, tmport);
	inb(0x80);		/* 2 deskew delay(45ns*2=90ns) */
	val &= 0x007f;		/* no bsy  */
	outw(val, tmport);
	mdelay(128);
	val &= 0x00fb;		/* after 1ms no msg */
	outw(val, tmport);
wait_nomsg:
	if ((inb(tmport) & 0x04) != 0) {
		goto wait_nomsg;
	}
	outb(1, 0x80);
	udelay(100);
	for (n = 0; n < 0x30000; n++) {
		if ((inb(tmport) & 0x80) != 0) {	/* bsy ? */
			goto wait_io;
		}
	}
	goto TCM_SYNC;
wait_io:
	for (n = 0; n < 0x30000; n++) {
		if ((inb(tmport) & 0x81) == 0x0081) {
			goto wait_io1;
		}
	}
	goto TCM_SYNC;
wait_io1:
	inb(0x80);
	val |= 0x8003;		/* io,cd,db7  */
	outw(val, tmport);
	inb(0x80);
	val &= 0x00bf;		/* no sel     */
	outw(val, tmport);
	outb(2, 0x80);
TCM_SYNC:
	udelay(0x800);
	if ((inb(tmport) & 0x80) == 0x00) {	/* bsy ? */
		outw(0, tmport--);
		outb(0, tmport);
		tmport = dev->ioport[0] + 0x15;
		outb(0, tmport);
		tmport += 0x03;
		outb(0x09, tmport);
		tmport += 0x07;
		while ((inb(tmport) & 0x80) == 0)
			cpu_relax();
		tmport -= 0x08;
		inb(tmport);
		return;
	}
	val &= 0x00ff;		/* synchronization  */
	val |= 0x3f00;
	fun_scam(dev, &val);
	outb(3, 0x80);
	val &= 0x00ff;		/* isolation        */
	val |= 0x2000;
	fun_scam(dev, &val);
	outb(4, 0x80);
	i = 8;
	j = 0;
TCM_ID:
	if ((inw(tmport) & 0x2000) == 0) {
		goto TCM_ID;
	}
	outb(5, 0x80);
	val &= 0x00ff;		/* get ID_STRING */
	val |= 0x2000;
	k = fun_scam(dev, &val);
	if ((k & 0x03) == 0) {
		goto TCM_5;
	}
	mbuf[j] <<= 0x01;
	mbuf[j] &= 0xfe;
	if ((k & 0x02) != 0) {
		mbuf[j] |= 0x01;
	}
	i--;
	if (i > 0) {
		goto TCM_ID;
	}
	j++;
	i = 8;
	goto TCM_ID;

TCM_5:			/* isolation complete..  */
/*    mbuf[32]=0;
	printk(" \n%x %x %x %s\n ",assignid_map,mbuf[0],mbuf[1],&mbuf[2]); */
	i = 15;
	j = mbuf[0];
	if ((j & 0x20) != 0) {	/* bit5=1:ID upto 7      */
		i = 7;
	}
	if ((j & 0x06) == 0) {	/* IDvalid?             */
		goto G2Q5;
	}
	k = mbuf[1];
small_id:
	m = 1;
	m <<= k;
	if ((m & assignid_map) == 0) {
		goto G2Q_QUIN;
	}
	if (k > 0) {
		k--;
		goto small_id;
	}
G2Q5:			/* srch from max acceptable ID#  */
	k = i;			/* max acceptable ID#            */
G2Q_LP:
	m = 1;
	m <<= k;
	if ((m & assignid_map) == 0) {
		goto G2Q_QUIN;
	}
	if (k > 0) {
		k--;
		goto G2Q_LP;
	}
G2Q_QUIN:		/* k=binID#,       */
	assignid_map |= m;
	if (k < 8) {
		quintet[0] = 0x38;	/* 1st dft ID<8    */
	} else {
		quintet[0] = 0x31;	/* 1st  ID>=8      */
	}
	k &= 0x07;
	quintet[1] = g2q_tab[k];

	val &= 0x00ff;		/* AssignID 1stQuintet,AH=001xxxxx  */
	m = quintet[0] << 8;
	val |= m;
	fun_scam(dev, &val);
	val &= 0x00ff;		/* AssignID 2ndQuintet,AH=001xxxxx */
	m = quintet[1] << 8;
	val |= m;
	fun_scam(dev, &val);

	goto TCM_SYNC;

}