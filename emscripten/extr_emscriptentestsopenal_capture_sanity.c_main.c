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

/* Variables and functions */
 int /*<<< orphan*/  ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER ; 
 int /*<<< orphan*/  ALC_CAPTURE_DEVICE_SPECIFIER ; 
 char* alcGetString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_device_sanity (char const*) ; 
 int /*<<< orphan*/  end_test () ; 
 int /*<<< orphan*/  is_defaultname_in_names (char const*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (char const*) ; 

int main() {

    const char *dft = alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
    const char *names = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);

    if(!is_defaultname_in_names(dft, names)) {
        printf(
            "The default device specifier (\"%s\") was not found amongst the device specifier list : ...\n"
            , dft
        );
        for(const char *name = names; *name ; name += 1+strlen(name)) {
            printf("- \"%s\";\n", name);
        }
        printf("... this is not an error, though.\n\n");
    }

    for(const char *name = names; *name ; name += 1+strlen(name)) {
        check_device_sanity(name);
    }

    end_test();
}