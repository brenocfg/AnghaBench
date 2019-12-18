#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__** streams; } ;
struct TYPE_7__ {int /*<<< orphan*/  codec_id; } ;
struct TYPE_6__ {TYPE_2__* codec; } ;
typedef  TYPE_2__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_LOG_ERROR ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 scalar_t__ avcodec_open2 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* fctx ; 
 int /*<<< orphan*/  log_cb (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool open_codec(AVCodecContext **ctx, unsigned index)
{
   AVCodec *codec = avcodec_find_decoder(fctx->streams[index]->codec->codec_id);

   if (!codec)
   {
      log_cb(RETRO_LOG_ERROR, "Couldn't find suitable decoder, exiting ... \n");
      return false;
   }

   *ctx = fctx->streams[index]->codec;
   if (avcodec_open2(*ctx, codec, NULL) < 0)
      return false;

   return true;
}