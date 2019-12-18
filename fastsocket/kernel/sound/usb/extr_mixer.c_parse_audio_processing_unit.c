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
struct mixer_build {int dummy; } ;

/* Variables and functions */
 int build_audio_procunit (struct mixer_build*,int,void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  procunits ; 

__attribute__((used)) static int parse_audio_processing_unit(struct mixer_build *state, int unitid, void *raw_desc)
{
	return build_audio_procunit(state, unitid, raw_desc, procunits, "Processing Unit");
}