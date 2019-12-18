#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  easy; int /*<<< orphan*/  filename; int /*<<< orphan*/  name; int /*<<< orphan*/  mimetype; int /*<<< orphan*/  userheaders; int /*<<< orphan*/  curlheaders; } ;
typedef  TYPE_1__ curl_mimepart ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_mime_initpart (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int MIME_USERHEADERS_OWNER ; 
 int /*<<< orphan*/  cleanup_part_content (TYPE_1__*) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ ) ; 

void Curl_mime_cleanpart(curl_mimepart *part)
{
  cleanup_part_content(part);
  curl_slist_free_all(part->curlheaders);
  if(part->flags & MIME_USERHEADERS_OWNER)
    curl_slist_free_all(part->userheaders);
  Curl_safefree(part->mimetype);
  Curl_safefree(part->name);
  Curl_safefree(part->filename);
  Curl_mime_initpart(part, part->easy);
}