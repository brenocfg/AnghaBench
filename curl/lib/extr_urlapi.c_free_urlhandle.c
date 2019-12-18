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
struct Curl_URL {int /*<<< orphan*/  temppath; int /*<<< orphan*/  scratch; int /*<<< orphan*/  fragment; int /*<<< orphan*/  query; int /*<<< orphan*/  path; int /*<<< orphan*/  port; int /*<<< orphan*/  zoneid; int /*<<< orphan*/  host; int /*<<< orphan*/  options; int /*<<< orphan*/  password; int /*<<< orphan*/  user; int /*<<< orphan*/  scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_urlhandle(struct Curl_URL *u)
{
  free(u->scheme);
  free(u->user);
  free(u->password);
  free(u->options);
  free(u->host);
  free(u->zoneid);
  free(u->port);
  free(u->path);
  free(u->query);
  free(u->fragment);
  free(u->scratch);
  free(u->temppath);
}