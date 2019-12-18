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
struct TYPE_3__ {scalar_t__ fp; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ curl_mimepart ;

/* Variables and functions */
 scalar_t__ fopen_read (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mime_open_file(curl_mimepart * part)
{
  /* Open a MIMEKIND_FILE part. */

  if(part->fp)
    return 0;
  part->fp = fopen_read(part->data, "rb");
  return part->fp? 0: -1;
}