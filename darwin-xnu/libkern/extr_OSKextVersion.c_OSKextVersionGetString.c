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
typedef  int uint32_t ;
typedef  int OSKextVersion ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int VERS_MAJOR_MAX ; 
 int VERS_MAJOR_MULT ; 
 int VERS_MINOR_MULT ; 
 int VERS_REVISION_MULT ; 
 int VERS_STAGE_LEVEL_MAX ; 
 int VERS_STAGE_MULT ; 
 char* __OSKextVersionStringForStage (int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int kOSKextVersionMaxLength ; 
 int kOSKextVersionStageRelease ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strlen (char const*) ; 

Boolean OSKextVersionGetString(
    OSKextVersion   aVersion,
    char          * buffer,
    uint32_t        bufferLength)
{
    int             cpos = 0;
    OSKextVersion   vers_major = 0;
    OSKextVersion   vers_minor = 0;
    OSKextVersion   vers_revision = 0;
    OSKextVersion   vers_stage = 0;
    OSKextVersion   vers_stage_level = 0;
    const char    * stage_string = NULL;  // don't free

   /* No buffer or length less than longest possible vers string,
    * return 0.
    */
    if (!buffer || bufferLength < kOSKextVersionMaxLength) {
        return FALSE;
    }

    bzero(buffer, bufferLength * sizeof(char));

    if (aVersion < 0) {
        strlcpy(buffer, "(invalid)", bufferLength);
        return TRUE;
    }
    if (aVersion == 0) {
        strlcpy(buffer, "(missing)", bufferLength);
        return TRUE;
    }

    vers_major = aVersion / VERS_MAJOR_MULT;
    if (vers_major > VERS_MAJOR_MAX) {
        strlcpy(buffer, "(invalid)", bufferLength);
        return TRUE;
    }

    vers_minor = aVersion - (vers_major * VERS_MAJOR_MULT);
    vers_minor /= VERS_MINOR_MULT;

    vers_revision = aVersion -
        ( (vers_major * VERS_MAJOR_MULT) + (vers_minor * VERS_MINOR_MULT) );
    vers_revision /= VERS_REVISION_MULT;

    vers_stage = aVersion -
        ( (vers_major * VERS_MAJOR_MULT) + (vers_minor * VERS_MINOR_MULT) +
          (vers_revision * VERS_REVISION_MULT));
    vers_stage /= VERS_STAGE_MULT;

    vers_stage_level = aVersion -
        ( (vers_major * VERS_MAJOR_MULT) + (vers_minor * VERS_MINOR_MULT) +
          (vers_revision * VERS_REVISION_MULT) + (vers_stage * VERS_STAGE_MULT));
    if (vers_stage_level > VERS_STAGE_LEVEL_MAX) {
        strlcpy(buffer, "(invalid)", bufferLength);
        return TRUE;
    }

    cpos = snprintf(buffer, bufferLength, "%u", (uint32_t)vers_major);

   /* Always include the minor version; it just looks weird without.
    */
    buffer[cpos] = '.';
    cpos++;
    cpos += snprintf(buffer+cpos, bufferLength - cpos, "%u", (uint32_t)vers_minor);

   /* The revision is displayed only if nonzero.
    */
    if (vers_revision) {
        buffer[cpos] = '.';
        cpos++;
        cpos += snprintf(buffer+cpos, bufferLength - cpos, "%u",
			(uint32_t)vers_revision);
    }

    stage_string = __OSKextVersionStringForStage(vers_stage);
    if (!stage_string) {
        strlcpy(buffer, "(invalid)", bufferLength);
        return TRUE;
    }
    if (stage_string[0]) {
        strlcat(buffer, stage_string, bufferLength);
        cpos += strlen(stage_string);
    }

    if (vers_stage < kOSKextVersionStageRelease) {
        snprintf(buffer+cpos, bufferLength - cpos, "%u", (uint32_t)vers_stage_level);
    }

    return TRUE;
}