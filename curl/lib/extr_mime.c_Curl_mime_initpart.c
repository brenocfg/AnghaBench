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
struct Curl_easy {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; struct Curl_easy* easy; } ;
typedef  TYPE_1__ curl_mimepart ;

/* Variables and functions */
 int /*<<< orphan*/  MIMESTATE_BEGIN ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mimesetstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void Curl_mime_initpart(curl_mimepart *part, struct Curl_easy *easy)
{
  memset((char *) part, 0, sizeof(*part));
  part->easy = easy;
  mimesetstate(&part->state, MIMESTATE_BEGIN, NULL);
}