#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* c; } ;
typedef  TYPE_3__ bot_character_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_6__ {int integer; scalar_t__ _float; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ value; } ;

/* Variables and functions */
 TYPE_3__* BotCharacterFromHandle (int) ; 
 scalar_t__ CT_FLOAT ; 
 scalar_t__ CT_INTEGER ; 
 int /*<<< orphan*/  CheckCharacteristicIndex (int,int) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_4__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

int Characteristic_Integer(int character, int index)
{
	bot_character_t *ch;

	ch = BotCharacterFromHandle(character);
	if (!ch) return 0;
	//check if the index is in range
	if (!CheckCharacteristicIndex(character, index)) return 0;
	//an integer will just be returned
	if (ch->c[index].type == CT_INTEGER)
	{
		return ch->c[index].value.integer;
	} //end if
	//floats are casted to integers
	else if (ch->c[index].type == CT_FLOAT)
	{
		return (int) ch->c[index].value._float;
	} //end else if
	else
	{
		botimport.Print(PRT_ERROR, "characteristic %d is not a integer\n", index);
		return 0;
	} //end else if
//	return 0;
}