#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ size; int pos; } ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;
typedef  TYPE_1__ BufferReader ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 

__attribute__((used)) static OPJ_BOOL stream_seek(OPJ_OFF_T nb_bytes, void *user_data)
{
    BufferReader *reader = user_data;
    if (nb_bytes < 0 || nb_bytes > reader->size) {
        return OPJ_FALSE;
    }
    reader->pos = (int)nb_bytes;
    return OPJ_TRUE;
}