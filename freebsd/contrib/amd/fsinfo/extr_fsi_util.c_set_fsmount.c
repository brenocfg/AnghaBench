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
struct TYPE_3__ {int f_mask; char* f_localname; char* f_volname; char* f_fstype; char* f_opts; char* f_from; } ;
typedef  TYPE_1__ fsmount ;

/* Variables and functions */
#define  FM_DIRECT 133 
#define  FM_FROM 132 
#define  FM_FSTYPE 131 
#define  FM_LOCALNAME 130 
#define  FM_OPTS 129 
#define  FM_VOLNAME 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fsi_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fsmount_strings ; 

void
set_fsmount(fsmount *fp, int k, char *v)
{
  int m = 1 << k;

  if (fp->f_mask & m) {
    fsi_error("mount field \"%s\" already set", fsmount_strings[k]);
    return;
  }
  fp->f_mask |= m;

  switch (k) {

  case FM_LOCALNAME:
    fp->f_localname = v;
    break;

  case FM_VOLNAME:
    fp->f_volname = v;
    break;

  case FM_FSTYPE:
    fp->f_fstype = v;
    break;

  case FM_OPTS:
    fp->f_opts = v;
    break;

  case FM_FROM:
    fp->f_from = v;
    break;

  case FM_DIRECT:
    break;

  default:
    abort();
    break;
  }
}