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

/* Variables and functions */
 int DCMD_PROC_GETALTREG ; 
 int DCMD_PROC_GETFPREG ; 
 int DCMD_PROC_GETGREG ; 
 int DCMD_PROC_SETALTREG ; 
 int DCMD_PROC_SETFPREG ; 
 int DCMD_PROC_SETGREG ; 
 scalar_t__ EOK ; 
#define  NTO_REG_ALT 131 
#define  NTO_REG_FLOAT 130 
#define  NTO_REG_GENERAL 129 
#define  NTO_REG_SYSTEM 128 
 int /*<<< orphan*/  ctl_fd ; 
 scalar_t__ devctl (int /*<<< orphan*/ ,int,char**,int,int*) ; 

__attribute__((used)) static int
get_regset (int regset, char *buf, int bufsize, int *regsize)
{
  int dev_get, dev_set;
  switch (regset)
    {
    case NTO_REG_GENERAL:
      dev_get = DCMD_PROC_GETGREG;
      dev_set = DCMD_PROC_SETGREG;
      break;

    case NTO_REG_FLOAT:
      dev_get = DCMD_PROC_GETFPREG;
      dev_set = DCMD_PROC_SETFPREG;
      break;

    case NTO_REG_ALT:
      dev_get = DCMD_PROC_GETALTREG;
      dev_set = DCMD_PROC_SETALTREG;
      break;

    case NTO_REG_SYSTEM:
    default:
      return -1;
    }
  if (devctl (ctl_fd, dev_get, &buf, bufsize, regsize) != EOK)
    return -1;

  return dev_set;
}