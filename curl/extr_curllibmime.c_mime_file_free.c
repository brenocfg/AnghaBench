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
struct TYPE_2__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__ curl_mimepart ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mime_file_free(void *ptr)
{
  curl_mimepart *part = (curl_mimepart *) ptr;

  if(part->fp) {
    fclose(part->fp);
    part->fp = NULL;
  }
  Curl_safefree(part->data);
  part->data = NULL;
}