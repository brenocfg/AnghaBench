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
typedef  int uint32_t ;
struct TYPE_2__ {int* text_start; int* text_pos; int* data_start; int* data_pos; int entry_point; int /*<<< orphan*/ * data_size; int /*<<< orphan*/ * text_size; } ;
typedef  TYPE_1__ dolheader ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_before_exec (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t load_dol_image(const void *dolstart)
{
	uint32_t i;
   dolheader *dolfile = NULL;

	if(!dolstart)
		return 0;

	dolfile = (dolheader *) dolstart;

	for (i = 0; i < 7; i++)
	{
		if ((!dolfile->text_size[i]) || (dolfile->text_start[i] < 0x100))
			continue;

		memcpy((void *) dolfile->text_start[i], dolstart + dolfile->text_pos[i], dolfile->text_size[i]);
		sync_before_exec((void *) dolfile->text_start[i], dolfile->text_size[i]);
	}

	for (i = 0; i < 11; i++)
	{
		if ((!dolfile->data_size[i]) || (dolfile->data_start[i] < 0x100))
			continue;

		memcpy((void *) dolfile->data_start[i], dolstart + dolfile->data_pos[i], dolfile->data_size[i]);
		sync_before_exec((void *) dolfile->data_start[i], dolfile->data_size[i]);
	}

	return dolfile->entry_point;
}