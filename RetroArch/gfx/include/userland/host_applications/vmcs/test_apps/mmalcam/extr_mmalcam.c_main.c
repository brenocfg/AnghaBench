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
typedef  int /*<<< orphan*/  VCOS_THREAD_ATTR_T ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_3__ {int zero_copy; scalar_t__ init_result; int /*<<< orphan*/  init_sem; int /*<<< orphan*/  encoder_stats; scalar_t__ uri; int /*<<< orphan*/  render_stats; int /*<<< orphan*/  camera_num; int /*<<< orphan*/  focus_test; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  vformat; int /*<<< orphan*/  layer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BIT_RATE ; 
 int /*<<< orphan*/  DEFAULT_CAM_NUM ; 
 int /*<<< orphan*/  DEFAULT_VIDEO_FORMAT ; 
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*) ; 
 scalar_t__ MMALCAM_INIT_SUCCESS ; 
 int /*<<< orphan*/  MMAL_PARAM_FOCUS_MAX ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  VIEWFINDER_LAYER ; 
 TYPE_1__ camcorder_behaviour ; 
 int /*<<< orphan*/  camcorder_thread ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (scalar_t__) ; 
 scalar_t__ sleepy_time ; 
 int stop ; 
 int /*<<< orphan*/  test_mmal_camcorder ; 
 int /*<<< orphan*/  test_mmalcam_dump_stats (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_parse_cmdline (int,char const**) ; 
 int /*<<< orphan*/  test_signal_handler ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_thread_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_thread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int main(int argc, const char **argv)
{
   VCOS_THREAD_ATTR_T attrs;
   VCOS_STATUS_T status;
   int result = 0;

   vcos_log_register("mmalcam", VCOS_LOG_CATEGORY);
   printf("MMAL Camera Test App\n");
   signal(SIGINT, test_signal_handler);

   camcorder_behaviour.layer = VIEWFINDER_LAYER;
   camcorder_behaviour.vformat = DEFAULT_VIDEO_FORMAT;
   camcorder_behaviour.zero_copy = 1;
   camcorder_behaviour.bit_rate = DEFAULT_BIT_RATE;
   camcorder_behaviour.focus_test = MMAL_PARAM_FOCUS_MAX;
   camcorder_behaviour.camera_num = DEFAULT_CAM_NUM;

   if(test_parse_cmdline(argc, argv))
   {
      result = -1;
      goto error;
   }

   status = vcos_semaphore_create(&camcorder_behaviour.init_sem, "mmalcam-init", 0);
   vcos_assert(status == VCOS_SUCCESS);

   vcos_thread_attr_init(&attrs);
   if (vcos_thread_create(&camcorder_thread, "mmal camcorder", &attrs, test_mmal_camcorder, &camcorder_behaviour) != VCOS_SUCCESS)
   {
      LOG_ERROR("Thread creation failure");
      result = -2;
      goto error;
   }

   vcos_semaphore_wait(&camcorder_behaviour.init_sem);
   if (camcorder_behaviour.init_result != MMALCAM_INIT_SUCCESS)
   {
      LOG_ERROR("Initialisation failed: %d", camcorder_behaviour.init_result);
      result = (int)camcorder_behaviour.init_result;
      goto error;
   }

   if (sleepy_time != 0)
   {
      sleep(sleepy_time);
      stop = 1;
   }

error:
   LOG_TRACE("Waiting for camcorder thread to terminate");
   vcos_thread_join(&camcorder_thread, NULL);

   test_mmalcam_dump_stats("Render", &camcorder_behaviour.render_stats);
   if (camcorder_behaviour.uri)
      test_mmalcam_dump_stats("Encoder", &camcorder_behaviour.encoder_stats);

   vcos_semaphore_delete(&camcorder_behaviour.init_sem);
   return result;
}