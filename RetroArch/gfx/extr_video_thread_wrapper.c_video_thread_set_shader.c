#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_video_t ;
struct TYPE_5__ {int type; char const* path; } ;
struct TYPE_6__ {int b; TYPE_1__ set_shader; } ;
struct TYPE_7__ {TYPE_2__ data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ thread_packet_t ;
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_SHADER ; 
 int /*<<< orphan*/  video_thread_send_and_wait_user_to_thread (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static bool video_thread_set_shader(void *data,
      enum rarch_shader_type type, const char *path)
{
   thread_video_t *thr = (thread_video_t*)data;
   thread_packet_t pkt = {CMD_SET_SHADER};
   if (!thr)
      return false;

   pkt.data.set_shader.type = type;
   pkt.data.set_shader.path = path;

   video_thread_send_and_wait_user_to_thread(thr, &pkt);

   return pkt.data.b;
}