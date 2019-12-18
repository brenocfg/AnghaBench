#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ expected_readorder; scalar_t__ cache_size; TYPE_1__* dialogue_cache; TYPE_1__* last_added_dialogue; } ;
struct TYPE_8__ {int /*<<< orphan*/  pb; TYPE_3__* priv_data; } ;
struct TYPE_7__ {scalar_t__ readorder; int /*<<< orphan*/ * prev; int /*<<< orphan*/  line; struct TYPE_7__* next; } ;
typedef  TYPE_1__ DialogueLine ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASSContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int,scalar_t__,...) ; 
 int /*<<< orphan*/  avio_print (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void purge_dialogues(AVFormatContext *s, int force)
{
    int n = 0;
    ASSContext *ass = s->priv_data;
    DialogueLine *dialogue = ass->dialogue_cache;

    while (dialogue && (dialogue->readorder == ass->expected_readorder || force)) {
        DialogueLine *next = dialogue->next;
        if (dialogue->readorder != ass->expected_readorder) {
            av_log(s, AV_LOG_WARNING, "ReadOrder gap found between %d and %d\n",
                   ass->expected_readorder, dialogue->readorder);
            ass->expected_readorder = dialogue->readorder;
        }
        avio_print(s->pb, "Dialogue: ", dialogue->line, "\r\n");
        if (dialogue == ass->last_added_dialogue)
            ass->last_added_dialogue = next;
        av_freep(&dialogue->line);
        av_free(dialogue);
        if (next)
            next->prev = NULL;
        dialogue = ass->dialogue_cache = next;
        ass->expected_readorder++;
        n++;
    }
    ass->cache_size -= n;
    if (n > 1)
        av_log(s, AV_LOG_DEBUG, "wrote %d ASS lines, cached dialogues: %d, waiting for event id %d\n",
               n, ass->cache_size, ass->expected_readorder);
}