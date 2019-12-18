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
 int Q_filelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SafeOpenRead (char const*) ; 
 int /*<<< orphan*/  SafeRead (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 

int    LoadFile( const char *filename, void **bufferptr )
{
	FILE	*f;
	int    length;
	void    *buffer;

	f = SafeOpenRead (filename);
	length = Q_filelength (f);
	buffer = malloc (length+1);
	((char *)buffer)[length] = 0;
	SafeRead (f, buffer, length);
	fclose (f);

	*bufferptr = buffer;
	return length;
}