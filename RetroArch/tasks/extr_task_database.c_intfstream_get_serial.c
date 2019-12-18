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
typedef  int /*<<< orphan*/  intfstream_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_FOUND_DISK_LABEL ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ detect_gc_game (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ detect_ps1_game (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ detect_psp_game (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ detect_serial_ascii_game (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ detect_system (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static int intfstream_get_serial(intfstream_t *fd, char *serial)
{
  const char *system_name = NULL;

  /* Check if the system was not auto-detected. */
  if (detect_system(fd, &system_name) < 0)
  {
    /* Attempt to read an ASCII serial, like Wii. */
    if (detect_serial_ascii_game(fd, serial))
    {
      /* ASCII serial (Wii) was detected. */
      RARCH_LOG("%s '%s'\n", msg_hash_to_str(MSG_FOUND_DISK_LABEL), serial);
      return 0;
    }

    /* Any other non-system specific detection methods? */
    return 0;
  }

  if (string_is_equal(system_name, "psp"))
  {
    if (detect_psp_game(fd, serial) == 0)
      return 0;
    RARCH_LOG("%s '%s'\n", msg_hash_to_str(MSG_FOUND_DISK_LABEL), serial);
  }
  else if (string_is_equal(system_name, "ps1"))
  {
    if (detect_ps1_game(fd, serial) == 0)
      return 0;
    RARCH_LOG("%s '%s'\n", msg_hash_to_str(MSG_FOUND_DISK_LABEL), serial);
  }
  else if (string_is_equal(system_name, "gc"))
  {
    if (detect_gc_game(fd, serial) == 0)
      return 0;
    RARCH_LOG("%s '%s'\n", msg_hash_to_str(MSG_FOUND_DISK_LABEL), serial);
  }
  else {
    return 0;
  }

  return 1;
}