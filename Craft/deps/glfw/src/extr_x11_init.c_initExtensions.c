#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * crtcs; int /*<<< orphan*/  ncrtc; } ;
typedef  TYPE_7__ XRRScreenResources ;
struct TYPE_12__ {int major; void* detectable; scalar_t__ available; scalar_t__ minor; int /*<<< orphan*/  errorBase; int /*<<< orphan*/  eventBase; int /*<<< orphan*/  majorOpcode; } ;
struct TYPE_11__ {int major; void* available; scalar_t__ minor; int /*<<< orphan*/  errorBase; int /*<<< orphan*/  eventBase; int /*<<< orphan*/  majorOpcode; } ;
struct TYPE_16__ {void* available; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_14__ {int major; int minor; void* gammaBroken; void* available; int /*<<< orphan*/  errorBase; int /*<<< orphan*/  eventBase; } ;
struct TYPE_13__ {int /*<<< orphan*/  errorBase; int /*<<< orphan*/  eventBase; int /*<<< orphan*/  available; } ;
struct TYPE_15__ {int /*<<< orphan*/  display; void* XdndSelection; void* XdndFinished; void* XdndLeave; void* XdndDrop; void* XdndActionCopy; void* XdndStatus; void* XdndPosition; void* XdndEnter; void* XdndAware; void* SAVE_TARGETS; void* CLIPBOARD_MANAGER; void* CLIPBOARD; void* MULTIPLE; void* TARGETS; void* GLFW_SELECTION; void* ATOM_PAIR; void* COMPOUND_STRING; void* UTF8_STRING; void* NULL_; TYPE_2__ xkb; TYPE_1__ xi; TYPE_6__ xinerama; TYPE_4__ randr; int /*<<< orphan*/  root; TYPE_3__ vidmode; void* MOTIF_WM_HINTS; void* WM_DELETE_WINDOW; void* WM_STATE; void* WM_PROTOCOLS; } ;
struct TYPE_18__ {TYPE_5__ x11; } ;
typedef  void* GLboolean ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 scalar_t__ BadRequest ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 void* GL_FALSE ; 
 void* GL_TRUE ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XF86VidModeQueryExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XIQueryVersion (int /*<<< orphan*/ ,int*,scalar_t__*) ; 
 void* XInternAtom (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ XQueryExtension (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XRRFreeScreenResources (TYPE_7__*) ; 
 int /*<<< orphan*/  XRRGetCrtcGammaSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* XRRGetScreenResources (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* XRRQueryExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XRRQueryVersion (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ XineramaIsActive (int /*<<< orphan*/ ) ; 
 scalar_t__ XineramaQueryExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XkbQueryExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 scalar_t__ XkbSetDetectableAutoRepeat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  createKeyTables () ; 
 int /*<<< orphan*/  detectEWMH () ; 

__attribute__((used)) static GLboolean initExtensions(void)
{
    // Find or create window manager atoms
    _glfw.x11.WM_PROTOCOLS = XInternAtom(_glfw.x11.display,
                                         "WM_PROTOCOLS",
                                         False);
    _glfw.x11.WM_STATE = XInternAtom(_glfw.x11.display, "WM_STATE", False);
    _glfw.x11.WM_DELETE_WINDOW = XInternAtom(_glfw.x11.display,
                                             "WM_DELETE_WINDOW",
                                             False);
    _glfw.x11.MOTIF_WM_HINTS = XInternAtom(_glfw.x11.display,
                                           "_MOTIF_WM_HINTS",
                                           False);

#if defined(_GLFW_HAS_XF86VM)
    // Check for XF86VidMode extension
    _glfw.x11.vidmode.available =
        XF86VidModeQueryExtension(_glfw.x11.display,
                                  &_glfw.x11.vidmode.eventBase,
                                  &_glfw.x11.vidmode.errorBase);
#endif /*_GLFW_HAS_XF86VM*/

    // Check for RandR extension
    _glfw.x11.randr.available =
        XRRQueryExtension(_glfw.x11.display,
                          &_glfw.x11.randr.eventBase,
                          &_glfw.x11.randr.errorBase);

    if (_glfw.x11.randr.available)
    {
        XRRScreenResources* sr;

        if (!XRRQueryVersion(_glfw.x11.display,
                             &_glfw.x11.randr.major,
                             &_glfw.x11.randr.minor))
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "X11: Failed to query RandR version");
            return GL_FALSE;
        }

        // The GLFW RandR path requires at least version 1.3
        if (_glfw.x11.randr.major == 1 && _glfw.x11.randr.minor < 3)
            _glfw.x11.randr.available = GL_FALSE;

        sr = XRRGetScreenResources(_glfw.x11.display, _glfw.x11.root);

        if (!sr->ncrtc || !XRRGetCrtcGammaSize(_glfw.x11.display, sr->crtcs[0]))
        {
            // This is either a headless system or an older Nvidia binary driver
            // with broken gamma support
            // Flag it as useless and fall back to Xf86VidMode gamma, if
            // available
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "X11: RandR gamma ramp support seems broken");
            _glfw.x11.randr.gammaBroken = GL_TRUE;
        }

        XRRFreeScreenResources(sr);
    }

    if (XineramaQueryExtension(_glfw.x11.display,
                               &_glfw.x11.xinerama.major,
                               &_glfw.x11.xinerama.minor))
    {
        if (XineramaIsActive(_glfw.x11.display))
            _glfw.x11.xinerama.available = GL_TRUE;
    }

#if defined(_GLFW_HAS_XINPUT)
    if (XQueryExtension(_glfw.x11.display,
                        "XInputExtension",
                        &_glfw.x11.xi.majorOpcode,
                        &_glfw.x11.xi.eventBase,
                        &_glfw.x11.xi.errorBase))
    {
        _glfw.x11.xi.major = 2;
        _glfw.x11.xi.minor = 0;

        if (XIQueryVersion(_glfw.x11.display,
                           &_glfw.x11.xi.major,
                           &_glfw.x11.xi.minor) != BadRequest)
        {
            _glfw.x11.xi.available = GL_TRUE;
        }
    }
#endif /*_GLFW_HAS_XINPUT*/

    // Check if Xkb is supported on this display
    _glfw.x11.xkb.major = 1;
    _glfw.x11.xkb.minor = 0;
    _glfw.x11.xkb.available =
        XkbQueryExtension(_glfw.x11.display,
                          &_glfw.x11.xkb.majorOpcode,
                          &_glfw.x11.xkb.eventBase,
                          &_glfw.x11.xkb.errorBase,
                          &_glfw.x11.xkb.major,
                          &_glfw.x11.xkb.minor);

    if (_glfw.x11.xkb.available)
    {
        Bool supported;

        if (XkbSetDetectableAutoRepeat(_glfw.x11.display, True, &supported))
        {
            if (supported)
                _glfw.x11.xkb.detectable = GL_TRUE;
        }
    }

    // Update the key code LUT
    // FIXME: We should listen to XkbMapNotify events to track changes to
    // the keyboard mapping.
    createKeyTables();

    // Detect whether an EWMH-conformant window manager is running
    detectEWMH();

    // Find or create string format atoms
    _glfw.x11.NULL_ = XInternAtom(_glfw.x11.display, "NULL", False);
    _glfw.x11.UTF8_STRING =
        XInternAtom(_glfw.x11.display, "UTF8_STRING", False);
    _glfw.x11.COMPOUND_STRING =
        XInternAtom(_glfw.x11.display, "COMPOUND_STRING", False);
    _glfw.x11.ATOM_PAIR = XInternAtom(_glfw.x11.display, "ATOM_PAIR", False);

    // Find or create selection property atom
    _glfw.x11.GLFW_SELECTION =
        XInternAtom(_glfw.x11.display, "GLFW_SELECTION", False);

    // Find or create standard clipboard atoms
    _glfw.x11.TARGETS = XInternAtom(_glfw.x11.display, "TARGETS", False);
    _glfw.x11.MULTIPLE = XInternAtom(_glfw.x11.display, "MULTIPLE", False);
    _glfw.x11.CLIPBOARD = XInternAtom(_glfw.x11.display, "CLIPBOARD", False);

    // Find or create clipboard manager atoms
    _glfw.x11.CLIPBOARD_MANAGER =
        XInternAtom(_glfw.x11.display, "CLIPBOARD_MANAGER", False);
    _glfw.x11.SAVE_TARGETS =
        XInternAtom(_glfw.x11.display, "SAVE_TARGETS", False);

    // Find Xdnd (drag and drop) atoms, if available
    _glfw.x11.XdndAware = XInternAtom(_glfw.x11.display, "XdndAware", True);
    _glfw.x11.XdndEnter = XInternAtom(_glfw.x11.display, "XdndEnter", True);
    _glfw.x11.XdndPosition = XInternAtom(_glfw.x11.display, "XdndPosition", True);
    _glfw.x11.XdndStatus = XInternAtom(_glfw.x11.display, "XdndStatus", True);
    _glfw.x11.XdndActionCopy = XInternAtom(_glfw.x11.display, "XdndActionCopy", True);
    _glfw.x11.XdndDrop = XInternAtom(_glfw.x11.display, "XdndDrop", True);
    _glfw.x11.XdndLeave = XInternAtom(_glfw.x11.display, "XdndLeave", True);
    _glfw.x11.XdndFinished = XInternAtom(_glfw.x11.display, "XdndFinished", True);
    _glfw.x11.XdndSelection = XInternAtom(_glfw.x11.display, "XdndSelection", True);

    return GL_TRUE;
}