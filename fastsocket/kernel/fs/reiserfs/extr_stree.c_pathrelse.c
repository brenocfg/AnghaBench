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
struct treepath {int path_length; } ;

/* Variables and functions */
 int ILLEGAL_PATH_ELEMENT_OFFSET ; 
 int /*<<< orphan*/  PATH_OFFSET_PBUFFER (struct treepath*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 

void pathrelse(struct treepath *search_path)
{
	int path_offset = search_path->path_length;

	RFALSE(path_offset < ILLEGAL_PATH_ELEMENT_OFFSET,
	       "PAP-5090: invalid path offset");

	while (path_offset > ILLEGAL_PATH_ELEMENT_OFFSET)
		brelse(PATH_OFFSET_PBUFFER(search_path, path_offset--));

	search_path->path_length = ILLEGAL_PATH_ELEMENT_OFFSET;
}