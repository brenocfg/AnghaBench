#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  d_name; } ;
struct TYPE_5__ {int count; TYPE_2__** namelist; } ;
typedef  TYPE_1__ STATE_T ;

/* Variables and functions */
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_1__* malloc (int) ; 
 int scandir (char const*,TYPE_2__***,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_compare ; 
 int /*<<< orphan*/  seq_filter ; 

__attribute__((used)) static STATE_T *read_state(const char *dir)
{
    STATE_T *state = malloc(sizeof(STATE_T));
    int i;

    if (state)
    {
	state->count = scandir(dir, &state->namelist, seq_filter, seq_compare);

	for (i = 0; i < state->count; i++)
	{
	    int num = atoi(state->namelist[i]->d_name);
	    if (i != num)
		error("Overlay sequence error");
	}
    }
    return state;
}