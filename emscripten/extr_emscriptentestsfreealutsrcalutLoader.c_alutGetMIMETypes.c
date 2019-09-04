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
typedef  int ALenum ;

/* Variables and functions */
 int /*<<< orphan*/  ALUT_ERROR_INVALID_ENUM ; 
#define  ALUT_LOADER_BUFFER 129 
#define  ALUT_LOADER_MEMORY 128 
 int /*<<< orphan*/  _alutSanityCheck () ; 
 int /*<<< orphan*/  _alutSetError (int /*<<< orphan*/ ) ; 

const char *alutGetMIMETypes(ALenum loader)
{
  if (!_alutSanityCheck())
  {
    return NULL;
  }

  /* We do not distinguish the loaders yet... */
  switch (loader)
  {
  case ALUT_LOADER_BUFFER:
    return "audio/basic,audio/x-raw,audio/x-wav";

  case ALUT_LOADER_MEMORY:
    return "audio/basic,audio/x-raw,audio/x-wav";

  default:
    _alutSetError(ALUT_ERROR_INVALID_ENUM);
    return NULL;
  }
}