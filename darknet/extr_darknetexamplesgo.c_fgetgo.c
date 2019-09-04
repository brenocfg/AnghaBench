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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 

char *fgetgo(FILE *fp)
{
    if(feof(fp)) return 0;
    size_t size = 96;
    char *line = malloc(size*sizeof(char));
    if(size != fread(line, sizeof(char), size, fp)){
        free(line);
        return 0;
    }

    return line;
}