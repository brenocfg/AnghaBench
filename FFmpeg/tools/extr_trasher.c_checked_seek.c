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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void checked_seek(FILE *stream, int64_t offset, int whence)
{
    offset = fseek(stream, offset, whence);
    if (offset < 0) {
        fprintf(stderr, "seek failed\n");
        exit(1);
    }
}