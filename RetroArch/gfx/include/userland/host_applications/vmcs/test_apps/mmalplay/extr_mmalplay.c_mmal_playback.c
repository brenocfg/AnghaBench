#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  render_layer; int /*<<< orphan*/  output_uri; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  uri; TYPE_1__ options; } ;
struct TYPE_7__ {int /*<<< orphan*/  disable_playback; int /*<<< orphan*/  render_layer; int /*<<< orphan*/  output_uri; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMALPLAY_T ;
typedef  TYPE_2__ MMALPLAY_OPTIONS_T ;
typedef  TYPE_3__ FILE_PLAY_INFO_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmalplay_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmalplay_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmalplay_play (int /*<<< orphan*/ *) ; 
 TYPE_2__ options ; 
 scalar_t__ unclean_exit ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *mmal_playback(void *id)
{
   FILE_PLAY_INFO_T *play_info = id;
   MMALPLAY_OPTIONS_T opts;
   MMAL_STATUS_T status;
   MMALPLAY_T *ctx;

   /* Setup the options */
   opts = options;
   opts.output_uri = play_info->options.output_uri;
   opts.render_layer = play_info->options.render_layer;

   vcos_mutex_lock(&play_info->lock);
   ctx = mmalplay_create(play_info->uri, &opts, &status);
   play_info->ctx = ctx;
   vcos_mutex_unlock(&play_info->lock);
   if (!ctx)
      goto end;

   if (!opts.disable_playback)
      status = mmalplay_play(ctx);

   if (unclean_exit)
      goto end;

   vcos_mutex_lock(&play_info->lock);
   if (ctx)
   {
      /* coverity[use] Suppress ATOMICITY warning - ctx might have changed since
       * we initialised it above, which is okay */
      mmalplay_destroy(ctx);
   }
   play_info->ctx = 0;
   vcos_mutex_unlock(&play_info->lock);

 end:
   LOG_TRACE("Thread %s terminating, result %d", play_info->name, status);
   play_info->status = status;
   return NULL;
}