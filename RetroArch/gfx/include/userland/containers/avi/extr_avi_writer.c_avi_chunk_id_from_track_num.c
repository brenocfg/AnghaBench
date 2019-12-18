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
typedef  int /*<<< orphan*/  track_num_buf ;
struct TYPE_6__ {TYPE_1__* format; } ;
typedef  TYPE_2__ VC_CONTAINER_TRACK_T ;
struct TYPE_7__ {TYPE_2__** tracks; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_5__ {scalar_t__ es_type; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  VC_FOURCC (char,unsigned char,char,char) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static void avi_chunk_id_from_track_num( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_FOURCC_T *p_chunk_id, unsigned int track_num )
{
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[track_num];
   VC_CONTAINER_FOURCC_T chunk_id = 0;
   char track_num_buf[3];

   if(track->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
      chunk_id = VC_FOURCC('0','0','d','c');
   else if(track->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO)
      chunk_id = VC_FOURCC('0','0','w','b');
   else
   {
      /* Note that avi_writer_add_track should ensure this
         can't happen */
      *p_chunk_id  = VC_FOURCC('J','U','N','K'); return;
   }

   snprintf(track_num_buf, sizeof(track_num_buf), "%02d", track_num);
   memcpy(&chunk_id, track_num_buf, 2);

   *p_chunk_id = chunk_id;
}