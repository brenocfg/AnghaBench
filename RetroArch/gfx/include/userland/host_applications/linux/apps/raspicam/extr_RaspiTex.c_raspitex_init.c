#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_10__ {int /*<<< orphan*/  completed_sem; int /*<<< orphan*/  start_sem; } ;
struct TYPE_11__ {int scene_id; TYPE_1__ capture; scalar_t__ verbose; } ;
typedef  TYPE_2__ RASPITEX_STATE ;

/* Variables and functions */
#define  RASPITEX_SCENE_MIRROR 133 
#define  RASPITEX_SCENE_SOBEL 132 
#define  RASPITEX_SCENE_SQUARE 131 
#define  RASPITEX_SCENE_TEAPOT 130 
#define  RASPITEX_SCENE_VCSM_SQUARE 129 
#define  RASPITEX_SCENE_YUV 128 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 int /*<<< orphan*/  VCOS_LOG_INFO ; 
 int /*<<< orphan*/  VCOS_LOG_WARN ; 
 scalar_t__ VCOS_SUCCESS ; 
 int mirror_open (TYPE_2__*) ; 
 int sobel_open (TYPE_2__*) ; 
 int square_open (TYPE_2__*) ; 
 int teapot_open (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_init () ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int) ; 
 int vcsm_square_open (TYPE_2__*) ; 
 int yuv_open (TYPE_2__*) ; 

int raspitex_init(RASPITEX_STATE *state)
{
   VCOS_STATUS_T status;
   int rc;
   vcos_init();

   vcos_log_register("RaspiTex", VCOS_LOG_CATEGORY);
   vcos_log_set_level(VCOS_LOG_CATEGORY,
                      state->verbose ? VCOS_LOG_INFO : VCOS_LOG_WARN);
   vcos_log_trace("%s", VCOS_FUNCTION);

   status = vcos_semaphore_create(&state->capture.start_sem,
                                  "glcap_start_sem", 1);
   if (status != VCOS_SUCCESS)
      goto error;

   status = vcos_semaphore_create(&state->capture.completed_sem,
                                  "glcap_completed_sem", 0);
   if (status != VCOS_SUCCESS)
      goto error;

   switch (state->scene_id)
   {
   case RASPITEX_SCENE_SQUARE:
      rc = square_open(state);
      break;
   case RASPITEX_SCENE_MIRROR:
      rc = mirror_open(state);
      break;
   case RASPITEX_SCENE_TEAPOT:
      rc = teapot_open(state);
      break;
   case RASPITEX_SCENE_YUV:
      rc = yuv_open(state);
      break;
   case RASPITEX_SCENE_SOBEL:
      rc = sobel_open(state);
      break;
   case RASPITEX_SCENE_VCSM_SQUARE:
      rc = vcsm_square_open(state);
      break;
   default:
      rc = -1;
      break;
   }
   if (rc != 0)
      goto error;

   return 0;

error:
   vcos_log_error("%s: failed", VCOS_FUNCTION);
   return -1;
}