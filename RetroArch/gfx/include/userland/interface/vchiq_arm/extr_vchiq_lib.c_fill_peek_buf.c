#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int peek_size; int /*<<< orphan*/  fd; scalar_t__ peek_buf; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ VCHI_SERVICE_T ;
typedef  scalar_t__ VCHI_FLAGS_T ;
struct TYPE_6__ {int blocking; scalar_t__ buf; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ VCHIQ_DEQUEUE_MESSAGE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MSGBUF_SIZE ; 
 int /*<<< orphan*/  RETRY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_IOC_DEQUEUE_MESSAGE ; 
 scalar_t__ VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE ; 
 scalar_t__ VCHI_FLAGS_NONE ; 
 scalar_t__ alloc_msgbuf () ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

__attribute__((used)) static int
fill_peek_buf(VCHI_SERVICE_T *service,
   VCHI_FLAGS_T flags)
{
   VCHIQ_DEQUEUE_MESSAGE_T args;
   int ret = 0;

   vcos_assert(flags == VCHI_FLAGS_NONE || flags == VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE);

   if (service->peek_size < 0)
   {
      if (!service->peek_buf)
         service->peek_buf = alloc_msgbuf();

      if (service->peek_buf)
      {
         args.handle = service->handle;
         args.blocking = (flags == VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE);
         args.bufsize = MSGBUF_SIZE;
         args.buf = service->peek_buf;

         RETRY(ret, ioctl(service->fd, VCHIQ_IOC_DEQUEUE_MESSAGE, &args));

         if (ret >= 0)
         {
            service->peek_size = ret;
            ret = 0;
         }
         else
         {
            ret = -1;
         }
      }
      else
      {
         ret = -1;
      }
   }

   return ret;
}