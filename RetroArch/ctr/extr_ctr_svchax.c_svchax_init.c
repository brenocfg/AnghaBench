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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  backdoor_fn ;
typedef  int Result ;

/* Variables and functions */
 int /*<<< orphan*/  APT_CheckNew3DS (int*) ; 
 scalar_t__ CURRENT_KPROCESS ; 
 scalar_t__ R_FAILED (int) ; 
 scalar_t__ SYSTEM_VERSION (int,int,int) ; 
 int __ctr_svchax ; 
 int __ctr_svchax_srv ; 
 scalar_t__ __service_ptr ; 
 int /*<<< orphan*/  do_memchunkhax1 () ; 
 int /*<<< orphan*/  do_memchunkhax2 () ; 
 scalar_t__ get_luma_version (scalar_t__*,scalar_t__*) ; 
 scalar_t__ k_enable_all_svcs ; 
 scalar_t__ osGetKernelVersion () ; 
 scalar_t__ read_kaddr (scalar_t__) ; 
 int /*<<< orphan*/  srvExit () ; 
 int /*<<< orphan*/  srvInit () ; 
 int /*<<< orphan*/  svc_7b (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_kaddr (scalar_t__,scalar_t__) ; 

Result svchax_init(bool patch_srv)
{
   bool isNew3DS;
   APT_CheckNew3DS(&isNew3DS);

   u32 kver = osGetKernelVersion();

   if (!__ctr_svchax)
   {
      if (__service_ptr)
      {
        u32 luma_major, luma_minor;

        if (kver > SYSTEM_VERSION(2, 50, 11) &&
            (R_FAILED(get_luma_version(&luma_major, &luma_minor) || luma_major < 8)))
          return -1;
        else if (kver > SYSTEM_VERSION(2, 46, 0) && kver <= SYSTEM_VERSION(2, 50, 11))
          do_memchunkhax2();
        else if (kver <= SYSTEM_VERSION(2, 46, 0))
          do_memchunkhax1();
      }

      svc_7b((backdoor_fn)k_enable_all_svcs, isNew3DS);

      __ctr_svchax = 1;
   }

   if (patch_srv && !__ctr_svchax_srv)
   {
      u32 PID_kaddr = read_kaddr(CURRENT_KPROCESS) + (isNew3DS ? 0xBC : (kver > SYSTEM_VERSION(2, 40, 0)) ? 0xB4 : 0xAC);
      u32 old_PID = read_kaddr(PID_kaddr);
      write_kaddr(PID_kaddr, 0);
      srvExit();
      srvInit();
      write_kaddr(PID_kaddr, old_PID);

      __ctr_svchax_srv = 1;
   }

   return 0;
}