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
typedef  int /*<<< orphan*/  SpvId ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (int /*<<< orphan*/ *,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (long) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_file(const char *path, SpvId **buffer, size_t *word_count)
{
	long len;
	FILE *file = fopen(path, "rb");

	if (!file)
		return -1;

	fseek(file, 0, SEEK_END);
	len = ftell(file);
	rewind(file);

	*buffer = malloc(len);
	if (fread(*buffer, 1, len, file) != (size_t)len)
	{
		fclose(file);
		free(*buffer);
		return -1;
	}

	fclose(file);
	*word_count = len / sizeof(SpvId);
	return 0;
}