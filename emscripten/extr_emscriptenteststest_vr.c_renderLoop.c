#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {char* member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_8__ VRLayerInit ;
struct TYPE_17__ {double x; double y; double z; } ;
struct TYPE_16__ {double x; double y; double z; } ;
struct TYPE_15__ {double x; double y; double z; double w; } ;
struct TYPE_14__ {double x; double y; double z; } ;
struct TYPE_13__ {double x; double y; double z; } ;
struct TYPE_12__ {double x; double y; double z; } ;
struct TYPE_18__ {int poseFlags; TYPE_6__ angularAcceleration; TYPE_5__ angularVelocity; TYPE_4__ orientation; TYPE_3__ linearAcceleration; TYPE_2__ linearVelocity; TYPE_1__ position; } ;
struct TYPE_20__ {int /*<<< orphan*/  rightViewMatrix; int /*<<< orphan*/  leftViewMatrix; int /*<<< orphan*/  rightProjectionMatrix; int /*<<< orphan*/  leftProjectionMatrix; TYPE_7__ pose; } ;
typedef  TYPE_9__ VRFrameData ;

/* Variables and functions */
 int /*<<< orphan*/  VR_LAYER_DEFAULT_LEFT_BOUNDS ; 
 int /*<<< orphan*/  VR_LAYER_DEFAULT_RIGHT_BOUNDS ; 
 int VR_POSE_ANGULAR_ACCELERATION ; 
 int VR_POSE_ANGULAR_VELOCITY ; 
 int VR_POSE_LINEAR_ACCELERATION ; 
 int VR_POSE_LINEAR_VELOCITY ; 
 int VR_POSE_ORIENTATION ; 
 int VR_POSE_POSITION ; 
 int /*<<< orphan*/  emscripten_vr_cancel_display_render_loop (int) ; 
 scalar_t__ emscripten_vr_display_presenting (int) ; 
 int /*<<< orphan*/  emscripten_vr_get_frame_data (int,TYPE_9__*) ; 
 int /*<<< orphan*/  emscripten_vr_request_present (int,TYPE_8__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_vr_set_display_render_loop_arg (int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  emscripten_vr_submit_frame (int) ; 
 int gDisplay ; 
 int /*<<< orphan*/  printMatrix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  renderLoopArg ; 
 int renderLoopCalled ; 
 int /*<<< orphan*/  report_result (int) ; 
 int /*<<< orphan*/  requestPresentCallback ; 

__attribute__((used)) static void renderLoop() {
    renderLoopCalled++;
    if(renderLoopCalled == 1) {
        /* First iteration */
        VRLayerInit init = {
            "#canvas",
            VR_LAYER_DEFAULT_LEFT_BOUNDS,
            VR_LAYER_DEFAULT_RIGHT_BOUNDS
        };
        if (!emscripten_vr_request_present(gDisplay, &init, 1, requestPresentCallback, NULL)) {
            printf("Request present with default canvas failed.\n");
            report_result(1);
            return;
        }

        if(emscripten_vr_display_presenting(gDisplay)) {
            /* request present needs to be called from a user gesture callback and
             * should have failed to make the display present. */
            printf("Error: Expected display not to be presenting.\n");
            report_result(1);
            return;
        }

        VRFrameData data;
        if (!emscripten_vr_get_frame_data(gDisplay, &data)) {
            printf("Could not get frame data. (first iteration)\n");
            report_result(1);
            return;
        }
        if(!emscripten_vr_submit_frame(gDisplay)) {
            printf("Error: Failed to submit frame to VR display %d (first iteration)\n", gDisplay);
            report_result(1);
            return;
        }
        return;
    } else if (renderLoopCalled > 2) {
        printf("Error: Unexpected render loop iteration\n");
        report_result(1);
        return; // only two iterations should run code
    }

    /* Second iteration */

    emscripten_vr_cancel_display_render_loop(gDisplay);

    VRFrameData data;
    if (!emscripten_vr_get_frame_data(gDisplay, &data)) {
        printf("Could not get frame data.\n");
        report_result(1);
    }

    /* Print list of properties which are reported as valid */
    printf("The following properties are valid:\n[");
    if(data.pose.poseFlags & VR_POSE_POSITION) {
        printf("position, ");
    }
    if(data.pose.poseFlags & VR_POSE_LINEAR_VELOCITY) {
        printf("linear vel, ");
    }
    if(data.pose.poseFlags & VR_POSE_LINEAR_ACCELERATION) {
        printf("linear accel, ");
    }
    if(data.pose.poseFlags & VR_POSE_ORIENTATION) {
        printf("orientation, ");
    }
    if(data.pose.poseFlags & VR_POSE_ANGULAR_VELOCITY) {
        printf("angular vel, ");
    }
    if(data.pose.poseFlags & VR_POSE_ANGULAR_ACCELERATION) {
        printf("angular accel");
    }
    printf("]\n");

    /* Print all values (independent of validity) */
    printf("Position: \t\t%f %f %f\n",
            data.pose.position.x,
            data.pose.position.y,
            data.pose.position.z);

    printf("Linear Velocity: \t%f %f %f\n",
            data.pose.linearVelocity.x,
            data.pose.linearVelocity.y,
            data.pose.linearVelocity.z);

    printf("Linear Acceleration: \t%f %f %f\n",
            data.pose.linearAcceleration.x,
            data.pose.linearAcceleration.y,
            data.pose.linearAcceleration.z);

    printf("Orientation: \t\t%f %f %f %f\n",
            data.pose.orientation.x,
            data.pose.orientation.y,
            data.pose.orientation.z,
            data.pose.orientation.w);

    printf("Angular Velocity: \t%f %f %f\n",
            data.pose.angularVelocity.x,
            data.pose.angularVelocity.y,
            data.pose.angularVelocity.z);

    printf("Angular Acceleration: \t%f %f %f\n",
            data.pose.angularAcceleration.x,
            data.pose.angularAcceleration.y,
            data.pose.angularAcceleration.z);

    printf("Left Projection Matrix:\n");
    printMatrix(data.leftProjectionMatrix);

    printf("Right Projection Matrix:\n");
    printMatrix(data.rightProjectionMatrix);

    printf("Left View Matrix:\n");
    printMatrix(data.leftViewMatrix);

    printf("Right View Matrix:\n");
    printMatrix(data.rightViewMatrix);

    if(!emscripten_vr_submit_frame(gDisplay)) {
        printf("Error: Failed to submit frame to VR display %d (second iteration)\n", gDisplay);
        report_result(1);
    }

    printf("Submitted frame.\n");

    if (!emscripten_vr_set_display_render_loop_arg(gDisplay, renderLoopArg, (void*) 42)) {
        printf("Error: Failed to dereference handle while settings display render loop of device %d\n", gDisplay);
        report_result(1);
    }

    printf("Set main loop with argument to be called next.\n");
}