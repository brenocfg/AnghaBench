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
struct TYPE_3__ {size_t source_index; } ;
typedef  TYPE_1__ OutputStream ;
typedef  int /*<<< orphan*/  InputStream ;

/* Variables and functions */
 int /*<<< orphan*/ ** input_streams ; 

__attribute__((used)) static InputStream *get_input_stream(OutputStream *ost)
{
    if (ost->source_index >= 0)
        return input_streams[ost->source_index];
    return NULL;
}