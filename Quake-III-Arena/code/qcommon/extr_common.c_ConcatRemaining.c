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
 int /*<<< orphan*/  Q_strcat (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* completionField ; 
 int /*<<< orphan*/  keyConcatArgs () ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static void ConcatRemaining( const char *src, const char *start ) {
	char *str;

	str = strstr(src, start);
	if (!str) {
		keyConcatArgs();
		return;
	}

	str += strlen(start);
	Q_strcat( completionField->buffer, sizeof( completionField->buffer ), str);
}