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
struct TYPE_3__ {int m_mask; char* m_volname; char* m_exportfs; char* m_sel; } ;
typedef  TYPE_1__ fsi_mount ;

/* Variables and functions */
#define  DM_EXPORTFS 130 
#define  DM_SEL 129 
#define  DM_VOLNAME 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  dict_add (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dict_of_volnames ; 
 int /*<<< orphan*/  fsi_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mount_strings ; 

void
set_mount(fsi_mount *mp, int k, char *v)
{
  int m = 1 << k;

  if (mp->m_mask & m) {
    fsi_error("mount tree field \"%s\" already set", mount_strings[k]);
    return;
  }
  mp->m_mask |= m;

  switch (k) {

  case DM_VOLNAME:
    dict_add(dict_of_volnames, v, (char *) mp);
    mp->m_volname = v;
    break;

  case DM_EXPORTFS:
    mp->m_exportfs = v;
    break;

  case DM_SEL:
    mp->m_sel = v;
    break;

  default:
    abort();
    break;
  }
}