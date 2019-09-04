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
struct TYPE_4__ {struct TYPE_4__* data; } ;
typedef  TYPE_1__ OutputStream ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

ALboolean _alutOutputStreamDestroy(OutputStream * stream)
{
  free(stream->data);
  free(stream);
  return AL_TRUE;
}