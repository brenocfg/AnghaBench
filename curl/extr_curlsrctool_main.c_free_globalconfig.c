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
struct GlobalConfig {int /*<<< orphan*/  libcurl; int /*<<< orphan*/ * trace_stream; scalar_t__ trace_fopened; int /*<<< orphan*/ * errors; scalar_t__ errors_fopened; int /*<<< orphan*/  trace_dump; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_globalconfig(struct GlobalConfig *config)
{
  Curl_safefree(config->trace_dump);

  if(config->errors_fopened && config->errors)
    fclose(config->errors);
  config->errors = NULL;

  if(config->trace_fopened && config->trace_stream)
    fclose(config->trace_stream);
  config->trace_stream = NULL;

  Curl_safefree(config->libcurl);
}