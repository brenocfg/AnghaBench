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
struct audio_mixer_userdata {int is_finished; int slot_selection_type; int slot_selection_idx; int /*<<< orphan*/  handle; struct audio_mixer_userdata* data; struct audio_mixer_userdata* path; struct audio_mixer_userdata* user_data; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  handler; struct audio_mixer_userdata* state; int /*<<< orphan*/  stream_type; int /*<<< orphan*/  status; int /*<<< orphan*/ * cb; int /*<<< orphan*/  callback; int /*<<< orphan*/  type; } ;
struct audio_mixer_handle {int is_finished; int slot_selection_type; int slot_selection_idx; int /*<<< orphan*/  handle; struct audio_mixer_handle* data; struct audio_mixer_handle* path; struct audio_mixer_handle* user_data; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  handler; struct audio_mixer_handle* state; int /*<<< orphan*/  stream_type; int /*<<< orphan*/  status; int /*<<< orphan*/ * cb; int /*<<< orphan*/  callback; int /*<<< orphan*/  type; } ;
typedef  struct audio_mixer_userdata retro_task_t ;
typedef  int /*<<< orphan*/ * retro_task_callback_t ;
typedef  struct audio_mixer_userdata nbio_handle_t ;
typedef  enum audio_mixer_slot_selection_type { ____Placeholder_audio_mixer_slot_selection_type } audio_mixer_slot_selection_type ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_FLAC ; 
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_MOD ; 
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_MP3 ; 
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_NONE ; 
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_OGG ; 
 int /*<<< orphan*/  AUDIO_MIXER_TYPE_WAV ; 
 int /*<<< orphan*/  AUDIO_STREAM_TYPE_SYSTEM ; 
 int /*<<< orphan*/  AUDIO_STREAM_TYPE_USER ; 
 int /*<<< orphan*/  NBIO_STATUS_INIT ; 
 int /*<<< orphan*/  NBIO_TYPE_FLAC ; 
 int /*<<< orphan*/  NBIO_TYPE_MOD ; 
 int /*<<< orphan*/  NBIO_TYPE_MP3 ; 
 int /*<<< orphan*/  NBIO_TYPE_NONE ; 
 int /*<<< orphan*/  NBIO_TYPE_OGG ; 
 int /*<<< orphan*/  NBIO_TYPE_WAV ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cb_nbio_audio_mixer_load ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct audio_mixer_userdata*) ; 
 int /*<<< orphan*/  nbio_free (int /*<<< orphan*/ ) ; 
 struct audio_mixer_userdata* strdup (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (struct audio_mixer_userdata*) ; 
 int /*<<< orphan*/  strlcpy (struct audio_mixer_userdata*,char const*,int) ; 
 scalar_t__ strstr (char const*,char*) ; 
 int /*<<< orphan*/  task_audio_mixer_handle_upload_flac ; 
 int /*<<< orphan*/  task_audio_mixer_handle_upload_mod ; 
 int /*<<< orphan*/  task_audio_mixer_handle_upload_mp3 ; 
 int /*<<< orphan*/  task_audio_mixer_handle_upload_ogg ; 
 int /*<<< orphan*/  task_audio_mixer_handle_upload_wav ; 
 int /*<<< orphan*/  task_audio_mixer_load_free ; 
 int /*<<< orphan*/  task_file_load_handler ; 
 struct audio_mixer_userdata* task_init () ; 
 int /*<<< orphan*/  task_queue_push (struct audio_mixer_userdata*) ; 

bool task_push_audio_mixer_load(
      const char *fullpath, retro_task_callback_t cb, void *user_data,
      bool system,
      enum audio_mixer_slot_selection_type slot_selection_type,
      int slot_selection_idx)
{
   nbio_handle_t             *nbio    = NULL;
   struct audio_mixer_handle   *mixer = NULL;
   retro_task_t                   *t  = task_init();
   struct audio_mixer_userdata *user  = (struct audio_mixer_userdata*)calloc(1, sizeof(*user));

   if (!t || !user)
      goto error;

   nbio               = (nbio_handle_t*)calloc(1, sizeof(*nbio));

   if (!nbio)
      goto error;

   nbio->path         = strdup(fullpath);

   mixer              = (struct audio_mixer_handle*)calloc(1, sizeof(*mixer));
   if (!mixer)
      goto error;

   mixer->is_finished = false;
   mixer->cb          = cb;

   strlcpy(mixer->path, fullpath, sizeof(mixer->path));

   nbio->type         = NBIO_TYPE_NONE;
   mixer->type        = AUDIO_MIXER_TYPE_NONE;

   if (strstr(fullpath, ".wav"))
   {
      mixer->type     = AUDIO_MIXER_TYPE_WAV;
      nbio->type      = NBIO_TYPE_WAV;
      t->callback     = task_audio_mixer_handle_upload_wav;
   }
   else if (strstr(fullpath, ".ogg"))
   {
      mixer->type     = AUDIO_MIXER_TYPE_OGG;
      nbio->type      = NBIO_TYPE_OGG;
      t->callback     = task_audio_mixer_handle_upload_ogg;
   }
   else if (strstr(fullpath, ".mp3"))
   {
      mixer->type     = AUDIO_MIXER_TYPE_MP3;
      nbio->type      = NBIO_TYPE_MP3;
      t->callback     = task_audio_mixer_handle_upload_mp3;
   }
   else if (strstr(fullpath, ".flac"))
   {
      mixer->type     = AUDIO_MIXER_TYPE_FLAC;
      nbio->type      = NBIO_TYPE_FLAC;
      t->callback     = task_audio_mixer_handle_upload_flac;
   }
   else if (	
         strstr(fullpath, ".mod") ||
         strstr(fullpath, ".s3m") ||
         strstr(fullpath, ".xm"))
   {
      mixer->type     = AUDIO_MIXER_TYPE_MOD;
      nbio->type      = NBIO_TYPE_MOD;
      t->callback     = task_audio_mixer_handle_upload_mod;
   }

   nbio->data         = (struct audio_mixer_handle*)mixer;
   nbio->is_finished  = false;
   nbio->cb           = &cb_nbio_audio_mixer_load;
   nbio->status       = NBIO_STATUS_INIT;

   if (system)
      user->stream_type      = AUDIO_STREAM_TYPE_SYSTEM;
   else
      user->stream_type      = AUDIO_STREAM_TYPE_USER;

   user->slot_selection_type = slot_selection_type;
   user->slot_selection_idx  = slot_selection_idx;

   t->state                  = nbio;
   t->handler                = task_file_load_handler;
   t->cleanup                = task_audio_mixer_load_free;
   t->user_data              = user;

   task_queue_push(t);

   return true;

error:
   if (nbio)
   {
      if (!string_is_empty(nbio->path))
         free(nbio->path);
      if (nbio->data)
         free(nbio->data);
      nbio_free(nbio->handle);
      free(nbio);
   }
   if (user)
      free(user);
   if (t)
      free(t);

   RARCH_ERR("[audio mixer load] Failed to open '%s': %s.\n",
         fullpath, strerror(errno));

   return false;
}