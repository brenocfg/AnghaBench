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
typedef  int /*<<< orphan*/  errorConf ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_LANGUAGE_EN ; 
 int /*<<< orphan*/  ERROR_TEXT ; 
 int /*<<< orphan*/  errorDisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errorInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errorText (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void errorAndQuit(const char* errorStr){
	errorConf error;

	errorInit(&error, ERROR_TEXT, CFG_LANGUAGE_EN);
	errorText(&error, errorStr);
	errorDisp(&error);
	exit(0);
}