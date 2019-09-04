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
typedef  scalar_t__ curl_off_t ;
struct TYPE_3__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ curl_mimepart ;

/* Variables and functions */
 int CURL_SEEKFUNC_CANTSEEK ; 
 int CURL_SEEKFUNC_FAIL ; 
 int CURL_SEEKFUNC_OK ; 
 int SEEK_SET ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,long,int) ; 
 scalar_t__ mime_open_file (TYPE_1__*) ; 

__attribute__((used)) static int mime_file_seek(void *instream, curl_off_t offset, int whence)
{
  curl_mimepart *part = (curl_mimepart *) instream;

  if(whence == SEEK_SET && !offset && !part->fp)
    return CURL_SEEKFUNC_OK;   /* Not open: implicitly already at BOF. */

  if(mime_open_file(part))
    return CURL_SEEKFUNC_FAIL;

  return fseek(part->fp, (long) offset, whence)?
               CURL_SEEKFUNC_CANTSEEK: CURL_SEEKFUNC_OK;
}