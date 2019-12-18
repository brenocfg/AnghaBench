#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int stream_copy; int finished; } ;
typedef  TYPE_1__ OutputStream ;
typedef  int /*<<< orphan*/  OptionsContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_ATTACHMENT ; 
 TYPE_1__* new_output_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static OutputStream *new_attachment_stream(OptionsContext *o, AVFormatContext *oc, int source_index)
{
    OutputStream *ost = new_output_stream(o, oc, AVMEDIA_TYPE_ATTACHMENT, source_index);
    ost->stream_copy = 1;
    ost->finished    = 1;
    return ost;
}