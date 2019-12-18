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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  result_t ;
typedef  int /*<<< orphan*/  ipc_request_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  int /*<<< orphan*/  ipc_buffer_t ;

/* Variables and functions */
 int HOSVER_MAJOR (int /*<<< orphan*/ ) ; 
 int HOSVER_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIB_ASSERT_OK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_ptrs ; 
 int /*<<< orphan*/  fail ; 
 int /*<<< orphan*/  fail_object ; 
 int /*<<< orphan*/  fail_sm ; 
 int /*<<< orphan*/  hosversionGet () ; 
 int /*<<< orphan*/  ipc_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_default_response_fmt ; 
 int /*<<< orphan*/  ipc_make_buffer (char*,int,int) ; 
 int /*<<< orphan*/  ipc_make_request (int) ; 
 int /*<<< orphan*/  ipc_msg_set_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sm_finalize () ; 
 int /*<<< orphan*/  sm_get_service (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sm_init () ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void frontend_switch_get_os(
      char *s, size_t len, int *major, int *minor)
{
#ifdef HAVE_LIBNX
   u32 hosVersion;
#else
   int patch;
   char firmware_version[0x100];
   result_t r; /* used by LIB_ASSERT_OK macros */
   ipc_object_t set_sys;
   ipc_request_t rq;
#endif

   strlcpy(s, "Horizon OS", len);

#ifdef HAVE_LIBNX
   *major = 0;
   *minor = 0;

   hosVersion = hosversionGet();
   *major     = HOSVER_MAJOR(hosVersion);
   *minor     = HOSVER_MINOR(hosVersion);
#else
   /* defaults in case we error out */
   *major     = 0;
   *minor     = 0;

   LIB_ASSERT_OK(fail, sm_init());
   LIB_ASSERT_OK(fail_sm, sm_get_service(&set_sys, "set:sys"));

   rq = ipc_make_request(3);
   ipc_buffer_t buffers[] = {
      ipc_make_buffer(firmware_version, 0x100, 0x1a),
   };
   ipc_msg_set_buffers(rq, buffers, buffer_ptrs);

   LIB_ASSERT_OK(fail_object, ipc_send(set_sys, &rq, &ipc_default_response_fmt));

   sscanf(firmware_version + 0x68, "%d.%d.%d", major, minor, &patch);

fail_object:
   ipc_close(set_sys);
fail_sm:
   sm_finalize();
fail:
   return;
#endif
}