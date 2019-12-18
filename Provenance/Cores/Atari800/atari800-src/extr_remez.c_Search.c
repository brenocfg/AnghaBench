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
 scalar_t__ Util_malloc (int) ; 
 scalar_t__ fabs (double const) ; 
 int /*<<< orphan*/  free (int*) ; 

__attribute__((used)) static void Search(int r, int Ext[], int gridsize, const double E[])
{
	int i, j, k, l, extra;     /* Counters */
	int up, alt;
	int *foundExt;             /* Array of found extremals */

	/* Allocate enough space for found extremals. */
	foundExt = (int *) Util_malloc((2 * r) * sizeof(int));
	k = 0;

	/* Check for extremum at 0. */
	if (((E[0] > 0.0) && (E[0] > E[1])) ||
	   ((E[0] < 0.0) && (E[0] < E[1])))
		foundExt[k++] = 0;

	/* Check for extrema inside dense grid */
	for (i = 1; i < gridsize - 1; i++) {
		if (((E[i] >= E[i - 1]) && (E[i] > E[i + 1]) && (E[i] > 0.0)) ||
		   ((E[i] <= E[i - 1]) && (E[i] < E[i + 1]) && (E[i] < 0.0)))
			foundExt[k++] = i;
	}

	/* Check for extremum at 0.5 */
	j = gridsize - 1;
	if (((E[j] > 0.0) && (E[j] > E[j - 1])) ||
	   ((E[j] < 0.0) && (E[j] < E[j - 1])))
		foundExt[k++] = j;

	/* Remove extra extremals */
	extra = k - (r + 1);

	while (extra > 0) {
		if (E[foundExt[0]] > 0.0)
			up = 1;                /* first one is a maxima */
		else
			up = 0;                /* first one is a minima */

		l = 0;
		alt = 1;
		for (j = 1; j < k; j++) {
			if (fabs(E[foundExt[j]]) < fabs(E[foundExt[l]]))
				l = j;              /* new smallest error. */
			if ((up) && (E[foundExt[j]] < 0.0))
				up = 0;             /* switch to a minima */
			else if ((!up) && (E[foundExt[j]] > 0.0))
				up = 1;             /* switch to a maxima */
			else {
				alt = 0;
				break;              /* Ooops, found two non-alternating */
			}                       /* extrema.  Delete smallest of them */
		}  /* if the loop finishes, all extrema are alternating */

		/* If there's only one extremal and all are alternating,
		 * delete the smallest of the first/last extremals. */
		if ((alt) && (extra == 1)) {
			if (fabs(E[foundExt[k - 1]]) < fabs(E[foundExt[0]]))
				l = foundExt[k - 1];   /* Delete last extremal */
			else
				l = foundExt[0];       /* Delete first extremal */
		}

		/* Loop that does the deletion */
		for (j = l; j < k; j++) {
			foundExt[j] = foundExt[j+1];
		}
		k--;
		extra--;
	}

	/* Copy found extremals to Ext[] */
	for (i = 0; i <= r; i++) {
		Ext[i] = foundExt[i];
	}

	free(foundExt);
}