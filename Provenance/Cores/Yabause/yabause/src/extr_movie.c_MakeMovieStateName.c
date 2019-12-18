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
struct TYPE_2__ {scalar_t__ Status; } ;

/* Variables and functions */
 TYPE_1__ Movie ; 
 scalar_t__ Playback ; 
 scalar_t__ Recording ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t const) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int strlen (char const*) ; 

const char *MakeMovieStateName(const char *filename) {

	static char *retbuf = NULL;  // Save the pointer to avoid memory leaks
	if(Movie.Status == Recording || Movie.Status == Playback) {
		const size_t newsize = strlen(filename) + 5 + 1;
		free(retbuf);
		retbuf = malloc(newsize);
		if (!retbuf) {
			return NULL;  // out of memory
		}
		sprintf(retbuf, "%smovie", filename);
		return retbuf;
	} else {
		return filename;  // unchanged
	}

}