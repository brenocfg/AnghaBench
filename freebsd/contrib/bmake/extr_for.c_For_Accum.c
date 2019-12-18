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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_AddByte (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOR ; 
 TYPE_1__* accumFor ; 
 int /*<<< orphan*/  debug_file ; 
 int forLevel ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int
For_Accum(char *line)
{
    char *ptr = line;

    if (*ptr == '.') {

	for (ptr++; *ptr && isspace((unsigned char) *ptr); ptr++)
	    continue;

	if (strncmp(ptr, "endfor", 6) == 0 &&
		(isspace((unsigned char) ptr[6]) || !ptr[6])) {
	    if (DEBUG(FOR))
		(void)fprintf(debug_file, "For: end for %d\n", forLevel);
	    if (--forLevel <= 0)
		return 0;
	} else if (strncmp(ptr, "for", 3) == 0 &&
		 isspace((unsigned char) ptr[3])) {
	    forLevel++;
	    if (DEBUG(FOR))
		(void)fprintf(debug_file, "For: new loop %d\n", forLevel);
	}
    }

    Buf_AddBytes(&accumFor->buf, strlen(line), line);
    Buf_AddByte(&accumFor->buf, '\n');
    return 1;
}