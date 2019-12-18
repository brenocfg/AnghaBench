#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_1__ sync_stream_t ;

/* Variables and functions */
 scalar_t__ SYNC_TYPE_AUDIO ; 
 scalar_t__ SYNC_TYPE_SUBTITLE ; 
 scalar_t__ SYNC_TYPE_VIDEO ; 
 int /*<<< orphan*/  dejitterAudio (TYPE_1__*) ; 
 int /*<<< orphan*/  dejitterVideo (TYPE_1__*) ; 
 int /*<<< orphan*/  fixAudioGap (TYPE_1__*) ; 
 int /*<<< orphan*/  fixAudioOverlap (TYPE_1__*) ; 
 int /*<<< orphan*/  fixSubtitleOverlap (TYPE_1__*) ; 
 int /*<<< orphan*/  fixVideoOverlap (TYPE_1__*) ; 

__attribute__((used)) static void fixStreamTimestamps( sync_stream_t * stream )
{
    // Fix gaps and overlaps in queue
    if (stream->type == SYNC_TYPE_AUDIO)
    {
        dejitterAudio(stream);
        fixAudioOverlap(stream);
        fixAudioGap(stream);
    }
    else if (stream->type == SYNC_TYPE_VIDEO)
    {
        dejitterVideo(stream);
        fixVideoOverlap(stream);
    }
    else if (stream->type == SYNC_TYPE_SUBTITLE)
    {
        fixSubtitleOverlap(stream);
    }
}