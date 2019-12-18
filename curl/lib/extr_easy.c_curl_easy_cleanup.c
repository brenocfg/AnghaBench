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
struct Curl_easy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_close (struct Curl_easy**) ; 
 int /*<<< orphan*/  SIGPIPE_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_st ; 
 int /*<<< orphan*/  sigpipe_ignore (struct Curl_easy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigpipe_restore (int /*<<< orphan*/ *) ; 

void curl_easy_cleanup(struct Curl_easy *data)
{
  SIGPIPE_VARIABLE(pipe_st);

  if(!data)
    return;

  sigpipe_ignore(data, &pipe_st);
  Curl_close(&data);
  sigpipe_restore(&pipe_st);
}