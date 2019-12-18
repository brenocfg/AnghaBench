#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t ESIFC ;

/* Variables and functions */
 size_t SIFC_COUNT ; 
 size_t SIFC_NONE ; 

inline const char* ESIFC_Name(ESIFC esifc)
{
	static const char * const names[] =
	{
		"<none>",
		"Arkanoid Paddle",
		"Hyper Shot gun",
		"4-Player Adapter",
		"Family Keyboard",
		"Subor Keyboard",
		"PEC586 Keyboard",
		"HyperShot Pads",
		"Mahjong",
		"Quiz King Buzzers",
		"Family Trainer A",
		"Family Trainer B",
		"Oeka Kids Tablet",
		"Barcode World",
		"Top Rider"
	};

	if(esifc >= SIFC_NONE && esifc <= SIFC_COUNT)
		return names[esifc];
	else return "<invalid ESIFC>";
}