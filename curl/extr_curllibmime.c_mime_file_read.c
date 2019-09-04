#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ curl_mimepart ;

/* Variables and functions */
 size_t READ_ERROR ; 
 size_t fread (char*,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ mime_open_file (TYPE_1__*) ; 

__attribute__((used)) static size_t mime_file_read(char *buffer, size_t size, size_t nitems,
                             void *instream)
{
  curl_mimepart *part = (curl_mimepart *) instream;

  if(mime_open_file(part))
    return READ_ERROR;

  return fread(buffer, size, nitems, part->fp);
}