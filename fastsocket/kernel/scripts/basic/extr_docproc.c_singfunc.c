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

/* Variables and functions */
 char* DOCBOOK ; 
 char* FUNCTION ; 
 char* KERNELDOC ; 
 int /*<<< orphan*/  exec_kernel_doc (char**) ; 
 scalar_t__ isspace (char) ; 

__attribute__((used)) static void singfunc(char * filename, char * line)
{
	char *vec[200]; /* Enough for specific functions */
        int i, idx = 0;
        int startofsym = 1;
	vec[idx++] = KERNELDOC;
	vec[idx++] = DOCBOOK;

        /* Split line up in individual parameters preceded by FUNCTION */
        for (i=0; line[i]; i++) {
                if (isspace(line[i])) {
                        line[i] = '\0';
                        startofsym = 1;
                        continue;
                }
                if (startofsym) {
                        startofsym = 0;
                        vec[idx++] = FUNCTION;
                        vec[idx++] = &line[i];
                }
        }
	vec[idx++] = filename;
	vec[idx] = NULL;
	exec_kernel_doc(vec);
}