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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int pat_len ; 
 int* patterns ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

void get_pattern (int pat_count, char *pats [])
{
	int ix, err, tmp;

#ifdef DEBUG
	fprintf (stderr,"get_pattern: count = %d\n", pat_count);
	for (ix = 0; ix < pat_count; ix++)
		fprintf (stderr, "  pat # %d:  [%s]\n", ix, pats[ix]);
#endif

	for (ix = 0; ix < pat_count; ix++) {
		tmp = 0;
		err = sscanf (pats[ix], "%5i", &tmp);
		if (err != 1 || tmp > 0xff) {
			fprintf (stderr, "pattern or value error in pattern # %d [%s]\n",
					ix, pats[ix]);
			usage ();
		}
		patterns [ix] = tmp;
	}
	pat_len = pat_count;
}