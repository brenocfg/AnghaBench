#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int quit; int /*<<< orphan*/  sem_decoded; int /*<<< orphan*/  sem_drawn; int /*<<< orphan*/  mutex; scalar_t__ stop_reason; } ;
typedef  TYPE_1__ VIDTEX_T ;
typedef  scalar_t__ VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 TYPE_1__* vcos_calloc (int,int,char*) ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 
 scalar_t__ vidtex_gl_init (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VIDTEX_T *vidtex_create(EGLNativeWindowType win)
{
   VIDTEX_T *vt;
   VCOS_STATUS_T st;

   vt = vcos_calloc(1, sizeof(*vt), "vidtex");
   if (vt == NULL)
   {
      vcos_log_trace("Memory allocation failure");
      return NULL;
   }

   st = vcos_semaphore_create(&vt->sem_decoded, "vidtex-dec", 0);
   if (st != VCOS_SUCCESS)
   {
      vcos_log_trace("Error creating semaphore");
      goto error_ctx;
   }

   st = vcos_semaphore_create(&vt->sem_drawn, "vidtex-drw", 0);
   if (st != VCOS_SUCCESS)
   {
      vcos_log_trace("Error creating semaphore");
      goto error_sem1;
   }

   st = vcos_mutex_create(&vt->mutex, "vidtex");
   if (st != VCOS_SUCCESS)
   {
      vcos_log_trace("Error creating semaphore");
      goto error_sem2;
   }

   if (vidtex_gl_init(vt, win) != 0)
   {
      vcos_log_trace("Error initialising EGL");
      goto error_mutex;
   }

   vt->quit = false;
   vt->stop_reason = 0;

   return vt;

error_mutex:
   vcos_mutex_delete(&vt->mutex);
error_sem2:
   vcos_semaphore_delete(&vt->sem_drawn);
error_sem1:
   vcos_semaphore_delete(&vt->sem_decoded);
error_ctx:
   vcos_free(vt);
   return NULL;
}