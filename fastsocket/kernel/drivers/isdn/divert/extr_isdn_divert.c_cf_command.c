#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
typedef  int u_char ;
struct TYPE_6__ {int proc; int timeout; int datalen; char* data; scalar_t__ ll_id; } ;
struct TYPE_7__ {TYPE_1__ dss1_io; } ;
struct TYPE_8__ {int driver; TYPE_2__ parm; int /*<<< orphan*/  arg; int /*<<< orphan*/  command; } ;
struct TYPE_9__ {scalar_t__ data; int /*<<< orphan*/  function; } ;
struct call_struc {char* info; struct call_struc* next; int /*<<< orphan*/ * prev; TYPE_3__ ics; TYPE_4__ timer; } ;
struct TYPE_10__ {int (* ll_cmd ) (TYPE_3__*) ;int /*<<< orphan*/  (* drv_to_name ) (int) ;} ;

/* Variables and functions */
 int DIVERT_ACTIVATE ; 
 int DIVERT_DEACTIVATE ; 
 int DIVERT_REPORT ; 
 int /*<<< orphan*/  DSS1_CMD_INVOKE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ISDN_CMD_PROT_IO ; 
 int /*<<< orphan*/  deflect_timer_expire ; 
 struct call_struc* divert_head ; 
 TYPE_5__ divert_if ; 
 int /*<<< orphan*/  divert_lock ; 
 int /*<<< orphan*/  init_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct call_struc*) ; 
 struct call_struc* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_id ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,scalar_t__,char*,int /*<<< orphan*/ ,char*,int,int,char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int stub2 (TYPE_3__*) ; 

int cf_command(int drvid, int mode, 
               u_char proc, char *msn, 
               u_char service, char *fwd_nr, ulong *procid)
{ unsigned long flags;
  int retval,msnlen;
  int fwd_len;
  char *p,*ielenp,tmp[60];
  struct call_struc *cs;

  if (strchr(msn,'.')) return(-EINVAL); /* subaddress not allowed in msn */
  if ((proc & 0x7F) > 2) return(-EINVAL);
  proc &= 3;
  p = tmp;
  *p++ = 0x30; /* enumeration */
  ielenp = p++; /* remember total length position */
  *p++ = 0xa; /* proc tag */
  *p++ = 1;   /* length */
  *p++ = proc & 0x7F; /* procedure to de/activate/interrogate */
  *p++ = 0xa; /* service tag */
  *p++ = 1;   /* length */
  *p++ = service; /* service to handle */

  if (mode == 1) 
   { if (!*fwd_nr) return(-EINVAL); /* destination missing */
     if (strchr(fwd_nr,'.')) return(-EINVAL); /* subaddress not allowed */
     fwd_len = strlen(fwd_nr);
     *p++ = 0x30; /* number enumeration */
     *p++ = fwd_len + 2; /* complete forward to len */ 
     *p++ = 0x80; /* fwd to nr */
     *p++ = fwd_len; /* length of number */
     strcpy(p,fwd_nr); /* copy number */
     p += fwd_len; /* pointer beyond fwd */
   } /* activate */

  msnlen = strlen(msn);
  *p++ = 0x80; /* msn number */
  if (msnlen > 1)
   { *p++ = msnlen; /* length */
     strcpy(p,msn);
     p += msnlen;
   }
  else *p++ = 0;

  *ielenp = p - ielenp - 1; /* set total IE length */ 

  /* allocate mem for information struct */  
  if (!(cs = kmalloc(sizeof(struct call_struc), GFP_ATOMIC)))
             return(-ENOMEM); /* no memory */
  init_timer(&cs->timer);
  cs->info[0] = '\0';
  cs->timer.function = deflect_timer_expire;
  cs->timer.data = (ulong) cs; /* pointer to own structure */
  cs->ics.driver = drvid;
  cs->ics.command = ISDN_CMD_PROT_IO; /* protocol specific io */
  cs->ics.arg = DSS1_CMD_INVOKE; /* invoke supplementary service */
  cs->ics.parm.dss1_io.proc = (mode == 1) ? 7: (mode == 2) ? 11:8; /* operation */ 
  cs->ics.parm.dss1_io.timeout = 4000; /* from ETS 300 207-1 */
  cs->ics.parm.dss1_io.datalen = p - tmp; /* total len */
  cs->ics.parm.dss1_io.data = tmp; /* start of buffer */
  
  spin_lock_irqsave(&divert_lock, flags);
  cs->ics.parm.dss1_io.ll_id = next_id++; /* id for callback */
  spin_unlock_irqrestore(&divert_lock, flags);
  *procid = cs->ics.parm.dss1_io.ll_id;  

  sprintf(cs->info,"%d 0x%lx %s%s 0 %s %02x %d%s%s\n",
	  (!mode ) ? DIVERT_DEACTIVATE : (mode == 1) ? DIVERT_ACTIVATE : DIVERT_REPORT,
          cs->ics.parm.dss1_io.ll_id,
          (mode != 2) ? "" : "0 ",
          divert_if.drv_to_name(cs->ics.driver),
          msn,
          service & 0xFF,
          proc,
          (mode != 1) ? "" : " 0 ",
          (mode != 1) ? "" : fwd_nr);
 
  retval = divert_if.ll_cmd(&cs->ics); /* execute command */

  if (!retval)
   { cs->prev = NULL;
     spin_lock_irqsave(&divert_lock, flags);
     cs->next = divert_head;
     divert_head = cs; 
     spin_unlock_irqrestore(&divert_lock, flags);
   }
  else
   kfree(cs);
  return(retval); 
}