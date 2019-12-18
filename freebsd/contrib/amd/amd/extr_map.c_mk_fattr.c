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
typedef  int nfsftype ;
struct TYPE_3__ {int na_type; int na_mode; int na_nlink; int na_size; } ;
typedef  TYPE_1__ nfsfattr ;

/* Variables and functions */
#define  NFDIR 129 
#define  NFLNK 128 
 int NFSMODE_DIR ; 
 int NFSMODE_LNK ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int) ; 

void
mk_fattr(nfsfattr *fattr, nfsftype vntype)
{
  switch (vntype) {
  case NFDIR:
    fattr->na_type = NFDIR;
    fattr->na_mode = NFSMODE_DIR | 0555;
    fattr->na_nlink = 2;
    fattr->na_size = 512;
    break;
  case NFLNK:
    fattr->na_type = NFLNK;
    fattr->na_mode = NFSMODE_LNK | 0777;
    fattr->na_nlink = 1;
    fattr->na_size = 0;
    break;
  default:
    plog(XLOG_FATAL, "Unknown fattr type %d - ignored", vntype);
    break;
  }
}