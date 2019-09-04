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
typedef  int /*<<< orphan*/  OSKextVersionStage ;

/* Variables and functions */
 int /*<<< orphan*/  __vers_isdigit (char const) ; 
 scalar_t__ __vers_isspace (char const) ; 
 int /*<<< orphan*/  kOSKextVersionStageAlpha ; 
 int /*<<< orphan*/  kOSKextVersionStageBeta ; 
 int /*<<< orphan*/  kOSKextVersionStageCandidate ; 
 int /*<<< orphan*/  kOSKextVersionStageDevelopment ; 
 int /*<<< orphan*/  kOSKextVersionStageInvalid ; 
 int /*<<< orphan*/  kOSKextVersionStageRelease ; 

__attribute__((used)) static OSKextVersionStage __OSKextVersionStageForString(const char ** string_p) {
    const char * string;

    if (!string_p || !*string_p) {
        return kOSKextVersionStageInvalid;
    }

    string = *string_p;

    if (__vers_isspace(string[0]) || string[0] == '\0') {
        return kOSKextVersionStageRelease;
    } else {
        switch (string[0]) {
          case 'd':
              if (__vers_isdigit(string[1])) {
                  *string_p = &string[1];
                  return kOSKextVersionStageDevelopment;
              }
              break;
          case 'a':
              if (__vers_isdigit(string[1])) {
                  *string_p = &string[1];
                  return kOSKextVersionStageAlpha;
              }
              break;
          case 'b':
              if (__vers_isdigit(string[1])) {
                  *string_p = &string[1];
                  return kOSKextVersionStageBeta;
              }
              break;
          case 'f':
              if (__vers_isdigit(string[1])) {
                  *string_p = &string[1];
                  return kOSKextVersionStageCandidate;
              } else if (string[1] == 'c' && __vers_isdigit(string[2])) {
                  *string_p = &string[2];
                  return kOSKextVersionStageCandidate;
              } else {
                  return kOSKextVersionStageInvalid;
              }
          default:
              return kOSKextVersionStageInvalid;
        }
    }

    return kOSKextVersionStageInvalid;
}