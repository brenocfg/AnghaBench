#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  m64p_handle ;
typedef  scalar_t__ eModeType ;
struct TYPE_4__ {TYPE_1__* control; } ;
struct TYPE_3__ {scalar_t__ Present; } ;

/* Variables and functions */
 scalar_t__ CONFIG_VERSION ; 
 int /*<<< orphan*/  ConfigDeleteSection (char*) ; 
 scalar_t__ ConfigGetParameter (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ConfigOpenSection (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConfigSaveSection (char*) ; 
 int /*<<< orphan*/  ConfigSetParameter (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int DEVICE_NO_JOYSTICK ; 
 int /*<<< orphan*/  DebugMessage (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ E_MODE_FULL_AUTO ; 
 scalar_t__ E_MODE_MANUAL ; 
 scalar_t__ E_MODE_NAMED_AUTO ; 
 scalar_t__ M64ERR_SUCCESS ; 
 int /*<<< orphan*/  M64MSG_ERROR ; 
 int /*<<< orphan*/  M64MSG_INFO ; 
 int /*<<< orphan*/  M64MSG_WARNING ; 
 int /*<<< orphan*/  M64TYPE_FLOAT ; 
 int /*<<< orphan*/  M64TYPE_INT ; 
 int /*<<< orphan*/  M64TYPE_STRING ; 
 int /*<<< orphan*/  auto_copy_inputconfig (char*,char*,char*) ; 
 int /*<<< orphan*/  auto_set_defaults (int,char*) ; 
 int /*<<< orphan*/  clear_controller (int) ; 
 TYPE_2__* controller ; 
 char* get_sdl_joystick_name (int) ; 
 int get_sdl_num_joysticks () ; 
 int /*<<< orphan*/  init_controller_config (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  load_controller_config (char*,int,int) ; 
 int setup_auto_controllers (int,int,int,char const*,scalar_t__*,scalar_t__*,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

void load_configuration(int bPreConfig)
{
    char SectionName[32];
    int joy_plugged = 0;
    int n64CtrlIdx, sdlCtrlIdx, j;
    int sdlNumDevUsed = 0;
    int sdlDevicesUsed[4];
    eModeType OrigControlMode[4], ControlMode[4];
    int ControlDevice[4];
    char DeviceName[4][256];
    int ActiveControllers = 0;
    int sdlNumJoysticks = get_sdl_num_joysticks();
    float fVersion = 0.0f;
    const char *sdl_name;
    int ControllersFound = 0;

    /* tell user how many SDL joysticks are available */
    if (!bPreConfig)
        DebugMessage(M64MSG_INFO, "%i SDL joysticks were found.", sdlNumJoysticks);

    /* loop through 4 N64 controllers, initializing and validating special section parameters */
    for (n64CtrlIdx=0; n64CtrlIdx < 4; n64CtrlIdx++)
    {
        m64p_handle pConfig;
        /* reset the controller configuration */
        clear_controller(n64CtrlIdx);

        /* Open the configuration section for this controller */
        sprintf(SectionName, "Input-SDL-Control%i", n64CtrlIdx + 1);
        if (ConfigOpenSection(SectionName, &pConfig) != M64ERR_SUCCESS)
        {
            // this should never happen
            DebugMessage(M64MSG_ERROR, "Couldn't open config section '%s'.  Aborting...", SectionName);
            return;
        }
        /* Check version number, and if it doesn't match: delete the config section */
        fVersion = 0.0f;
        if (ConfigGetParameter(pConfig, "version", M64TYPE_FLOAT, &fVersion, sizeof(float)) != M64ERR_SUCCESS || ((int) fVersion) != ((int) CONFIG_VERSION))
        {
            DebugMessage(M64MSG_WARNING, "Missing or incompatible config section '%s'. Clearing.", SectionName);
            ConfigDeleteSection(SectionName);
            // set local controller default parameters
            OrigControlMode[n64CtrlIdx] = ControlMode[n64CtrlIdx] = E_MODE_FULL_AUTO;
            ControlDevice[n64CtrlIdx] = DEVICE_NO_JOYSTICK;
            DeviceName[n64CtrlIdx][0] = 0;
            // write blank config for GUI front-ends
            init_controller_config(n64CtrlIdx, "", E_MODE_FULL_AUTO);
            // save it to the file too
            ConfigSaveSection(SectionName);
        }
        else
        {
            if (ConfigGetParameter(pConfig, "mode", M64TYPE_INT, &OrigControlMode[n64CtrlIdx], sizeof(int)) != M64ERR_SUCCESS ||
                (int) OrigControlMode[n64CtrlIdx] < 0 || (int) OrigControlMode[n64CtrlIdx] > 2)
            {
                if (!bPreConfig)
                    DebugMessage(M64MSG_WARNING, "Missing or invalid 'mode' parameter in config section '%s'.  Setting to 2 (Fully Auto)", SectionName);
                OrigControlMode[n64CtrlIdx] = E_MODE_FULL_AUTO;
            }
            ControlMode[n64CtrlIdx] = OrigControlMode[n64CtrlIdx];
            if (ConfigGetParameter(pConfig, "device", M64TYPE_INT, &ControlDevice[n64CtrlIdx], sizeof(int)) != M64ERR_SUCCESS)
            {
                if (!bPreConfig)
                    DebugMessage(M64MSG_WARNING, "Missing 'device' parameter in config section '%s'.  Setting to -1 (No joystick)", SectionName);
                ControlDevice[n64CtrlIdx] = DEVICE_NO_JOYSTICK;
            }
            if (ConfigGetParameter(pConfig, "name", M64TYPE_STRING, DeviceName[n64CtrlIdx], 256) != M64ERR_SUCCESS)
            {
                DeviceName[n64CtrlIdx][0] = 0;
            }
        }
    }

    /* loop through 4 N64 controllers and set up those in Fully Manual mode */
    for (n64CtrlIdx=0; n64CtrlIdx < 4; n64CtrlIdx++)
    {
        if (ControlMode[n64CtrlIdx] != E_MODE_MANUAL)
            continue;
        /* load the stored configuration (disregard any errors) */
        sprintf(SectionName, "Input-SDL-Control%i", n64CtrlIdx + 1);
        load_controller_config(SectionName, n64CtrlIdx, ControlDevice[n64CtrlIdx]);
        /* if this config uses an SDL joystick, mark it as used */
        if (ControlDevice[n64CtrlIdx] == DEVICE_NO_JOYSTICK)
        {
            if (!bPreConfig)
                DebugMessage(M64MSG_INFO, "N64 Controller #%i: Using manual config with no SDL joystick (keyboard/mouse only)", n64CtrlIdx+1);
        }
        else
        {
            sdlDevicesUsed[sdlNumDevUsed++] = ControlDevice[n64CtrlIdx];
            if (!bPreConfig)
                DebugMessage(M64MSG_INFO, "N64 Controller #%i: Using manual config for SDL joystick %i", n64CtrlIdx+1, ControlDevice[n64CtrlIdx]);
        }
        ActiveControllers++;
    }

    /* now loop through again, setting up those in Named Auto mode */
    for (n64CtrlIdx=0; n64CtrlIdx < 4; n64CtrlIdx++)
    {
        if (ControlMode[n64CtrlIdx] != E_MODE_NAMED_AUTO)
            continue;
        /* if name is empty, then use full auto mode instead */
        if (DeviceName[n64CtrlIdx][0] == 0)
        {
            ControlMode[n64CtrlIdx] = E_MODE_FULL_AUTO;
            continue;
        }
        sprintf(SectionName, "Input-SDL-Control%i", n64CtrlIdx + 1);
        /* if user is looking for a keyboard, set that up */
        if (strcasecmp(DeviceName[n64CtrlIdx], "Keyboard") == 0)
        {
            auto_set_defaults(DEVICE_NO_JOYSTICK, "Keyboard");
            if (load_controller_config("AutoConfig0", n64CtrlIdx, DEVICE_NO_JOYSTICK) > 0)
            {
                if (!bPreConfig)
                    DebugMessage(M64MSG_INFO, "N64 Controller #%i: Using auto-config for keyboard", n64CtrlIdx+1);
                /* copy the auto-config settings to the controller config section */
                auto_copy_inputconfig("AutoConfig0", SectionName, "Keyboard");
                ActiveControllers++;
                ConfigSaveSection(SectionName);
            }
            else
            {
                DebugMessage(M64MSG_ERROR, "Autoconfig keyboard setup invalid");
            }
            ConfigDeleteSection("AutoConfig0");
            continue;
        }
        /* search for an unused SDL device with the matching name */
        for (sdlCtrlIdx=0; sdlCtrlIdx < sdlNumJoysticks; sdlCtrlIdx++)
        {
            /* check if this one is in use */
            int deviceAlreadyUsed = 0;
            for (j = 0; j < sdlNumDevUsed; j++)
            {
                if (sdlDevicesUsed[j] == sdlCtrlIdx)
                    deviceAlreadyUsed = 1;
            }
            if (deviceAlreadyUsed)
                continue;
            /* check if the name matches */
            sdl_name = get_sdl_joystick_name(sdlCtrlIdx);
            if (sdl_name != NULL && strncmp(DeviceName[n64CtrlIdx], sdl_name, 255) == 0)
            {
                /* set up one or more controllers for this SDL device, if present in InputAutoConfig.ini */
                int ControllersFound = setup_auto_controllers(bPreConfig, n64CtrlIdx, sdlCtrlIdx, sdl_name, ControlMode, OrigControlMode, DeviceName);
                if (ControllersFound == 0)
                {
                    // error: no auto-config found for this SDL device
                    DebugMessage(M64MSG_ERROR, "No auto-config found for joystick named '%s' in InputAutoConfig.ini", sdl_name);
                    // mark this device as being used just so we don't complain about it again
                    sdlDevicesUsed[sdlNumDevUsed++] = sdlCtrlIdx;
                    // quit looking for SDL joysticks which match the name, because there's no valid autoconfig for that name.
                    // this controller will be unused; skip to the next one
                    break;
                }
                /* mark this sdl device as used */
                sdlDevicesUsed[sdlNumDevUsed++] = sdlCtrlIdx;
                ActiveControllers += ControllersFound;
                break;
            }
        }
        /* if we didn't find a match for this joystick name, then set the controller to fully auto */
        if (sdlCtrlIdx == sdlNumJoysticks)
        {
            if (!bPreConfig)
                DebugMessage(M64MSG_WARNING, "N64 Controller #%i: No SDL joystick found matching name '%s'.  Using full auto mode.", n64CtrlIdx+1, DeviceName[n64CtrlIdx]);
            ControlMode[n64CtrlIdx] = E_MODE_FULL_AUTO;
        }
    }

    /* Final loop through N64 controllers, setting up those in Full Auto mode */
    for (n64CtrlIdx=0; n64CtrlIdx < 4; n64CtrlIdx++)
    {
        if (ControlMode[n64CtrlIdx] != E_MODE_FULL_AUTO)
            continue;
        sprintf(SectionName, "Input-SDL-Control%i", n64CtrlIdx + 1);
        /* search for an unused SDL device */
        for (sdlCtrlIdx=0; sdlCtrlIdx < sdlNumJoysticks; sdlCtrlIdx++)
        {
            /* check if this one is in use */
            int deviceAlreadyUsed = 0;
            for (j = 0; j < sdlNumDevUsed; j++)
            {
                if (sdlDevicesUsed[j] == sdlCtrlIdx)
                    deviceAlreadyUsed = 1;
            }
            if (deviceAlreadyUsed)
                continue;
            /* set up one or more controllers for this SDL device, if present in InputAutoConfig.ini */
            sdl_name = get_sdl_joystick_name(sdlCtrlIdx);
            ControllersFound = setup_auto_controllers(bPreConfig, n64CtrlIdx, sdlCtrlIdx, sdl_name, ControlMode, OrigControlMode, DeviceName);
            if (!bPreConfig && ControllersFound == 0)
            {
                // error: no auto-config found for this SDL device
                DebugMessage(M64MSG_ERROR, "No auto-config found for joystick named '%s' in InputAutoConfig.ini", sdl_name);
                // mark this device as being used just so we don't complain about it again
                sdlDevicesUsed[sdlNumDevUsed++] = sdlCtrlIdx;
                // keep trying more SDL devices to see if we can auto-config one for this N64 controller
                continue;
            }
            /* mark this sdl device as used */
            sdlDevicesUsed[sdlNumDevUsed++] = sdlCtrlIdx;
            ActiveControllers += ControllersFound;
            break;
        }
        /* if this N64 controller was not activated, set device to -1 */
        if (sdlCtrlIdx == sdlNumJoysticks)
        {
            m64p_handle section;
            if (ConfigOpenSection(SectionName, &section) == M64ERR_SUCCESS)
            {
                const int iNoDevice = -1;
                ConfigSetParameter(section, "device", M64TYPE_INT, &iNoDevice);
                if (OrigControlMode[n64CtrlIdx] == E_MODE_FULL_AUTO)
                    ConfigSetParameter(section, "name", M64TYPE_STRING, "");
                ConfigSaveSection(SectionName);
            }
        }
    }

    /* fallback to keyboard if no controllers were configured */
    if (ActiveControllers == 0)
    {
        if (!bPreConfig)
            DebugMessage(M64MSG_INFO, "N64 Controller #1: Forcing default keyboard configuration");
        auto_set_defaults(DEVICE_NO_JOYSTICK, "Keyboard");
        if (load_controller_config("AutoConfig0", 0, DEVICE_NO_JOYSTICK) > 0)
        {
            /* copy the auto-config settings to the controller config section */
            if (OrigControlMode[0] == E_MODE_FULL_AUTO)
                auto_copy_inputconfig("AutoConfig0", "Input-SDL-Control1", "Keyboard");
            else
                auto_copy_inputconfig("AutoConfig0", "Input-SDL-Control1", NULL);  // don't overwrite 'name' parameter
            ActiveControllers++;
            ConfigSaveSection("Input-SDL-Control1");
        }
        else
        {
            DebugMessage(M64MSG_ERROR, "Autoconfig keyboard setup invalid");
        }
        ConfigDeleteSection("AutoConfig0");
    }

    /* see how many joysticks are plugged in */
    joy_plugged = 0;
    for (j = 0; j < 4; j++)
    {
        if (controller[j].control->Present)
            joy_plugged++;
    }

    /* print out summary info message */
    if (!bPreConfig)
    {
        if (joy_plugged > 0)
        {
            DebugMessage(M64MSG_INFO, "%i controller(s) found, %i plugged in and usable in the emulator", ActiveControllers, joy_plugged);
        }
        else
        {
            if (ActiveControllers == 0)
                DebugMessage(M64MSG_WARNING, "No joysticks/controllers found");
            else
                DebugMessage(M64MSG_WARNING, "%i controllers found, but none were 'plugged in'", ActiveControllers);
        }
    }

}