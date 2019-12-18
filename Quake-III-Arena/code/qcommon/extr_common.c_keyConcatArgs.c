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
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int Cmd_Argc () ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Q_strcat (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* completionField ; 

__attribute__((used)) static void keyConcatArgs( void ) {
	int		i;
	char	*arg;

	for ( i = 1 ; i < Cmd_Argc() ; i++ ) {
		Q_strcat( completionField->buffer, sizeof( completionField->buffer ), " " );
		arg = Cmd_Argv( i );
		while (*arg) {
			if (*arg == ' ') {
				Q_strcat( completionField->buffer, sizeof( completionField->buffer ),  "\"");
				break;
			}
			arg++;
		}
		Q_strcat( completionField->buffer, sizeof( completionField->buffer ),  Cmd_Argv( i ) );
		if (*arg == ' ') {
			Q_strcat( completionField->buffer, sizeof( completionField->buffer ),  "\"");
		}
	}
}