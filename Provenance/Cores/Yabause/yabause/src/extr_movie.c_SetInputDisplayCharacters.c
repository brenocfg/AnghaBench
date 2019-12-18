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
struct TYPE_2__ {int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/ * Buttons ; 
 int /*<<< orphan*/ * Buttons2 ; 
 char* InputDisplayString ; 
 TYPE_1__ PORTDATA1 ; 
 int /*<<< orphan*/ * Spaces ; 
 int /*<<< orphan*/ * Spaces2 ; 
 char* str ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void SetInputDisplayCharacters(void) {

	int x;

	strcpy(str, "");

	for (x = 0; x < 8; x++) {

		if(PORTDATA1.data[2] & (1 << x)) {
			strcat(str, Spaces[x]);	
		}
		else
			strcat(str, Buttons[x]);

	}

	for (x = 0; x < 8; x++) {

		if(PORTDATA1.data[3] & (1 << x)) {
			strcat(str, Spaces2[x]);	
		}
		else
			strcat(str, Buttons2[x]);

	}

	strcpy(InputDisplayString, str);
}