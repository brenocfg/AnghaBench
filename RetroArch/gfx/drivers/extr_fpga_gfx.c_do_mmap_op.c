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
struct TYPE_3__ {scalar_t__ only_munmap; int fd; scalar_t__ ptr; scalar_t__ only_mmap; } ;
typedef  TYPE_1__ RegOp ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_memory_size () ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_mmap_op(RegOp *regOp)
{
   if (regOp->only_munmap == 0)
   {
      regOp->fd = open("/dev/uio0", O_RDWR);

      if (regOp->fd < 1)
         return;

      regOp->ptr = mmap(NULL, get_memory_size(), PROT_READ|PROT_WRITE, MAP_SHARED, regOp->fd, 0);

      if (regOp->ptr == MAP_FAILED)
      {
         RARCH_ERR("could not mmap() memory\n");
         exit(1);
      }
   }

   if (regOp->only_mmap == 0)
   {
      if (munmap(regOp->ptr, get_memory_size()) == -1)
      {
         RARCH_ERR("could not munmap() memory\n");
         exit(1);
      }

      close(regOp->fd);
   }

   return;
}