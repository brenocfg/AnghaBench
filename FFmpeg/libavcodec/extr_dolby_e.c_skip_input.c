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
struct TYPE_3__ {int input_size; int input; int word_bytes; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ DBEContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int skip_input(DBEContext *s, int nb_words)
{
    if (nb_words > s->input_size) {
        av_log(s->avctx, AV_LOG_ERROR, "Packet too short\n");
        return AVERROR_INVALIDDATA;
    }

    s->input      += nb_words * s->word_bytes;
    s->input_size -= nb_words;
    return 0;
}