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
typedef  int /*<<< orphan*/  curl_mimepart ;

/* Variables and functions */
 size_t readback_part (int /*<<< orphan*/ *,char*,size_t) ; 

size_t Curl_mime_read(char *buffer, size_t size, size_t nitems, void *instream)
{
  curl_mimepart *part = (curl_mimepart *) instream;

  (void) size;   /* Always 1. */
  return readback_part(part, buffer, nitems);
}