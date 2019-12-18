__attribute__((used)) static void test_complex_designator() {
    struct { struct { int a, b; } x[3]; } y[] = {
        [1].x[0].b = 5, 6, 7, 8, 9,
        [0].x[2].b = 10, 11
    };
    expect(0, y[0].x[0].a);
    expect(0, y[0].x[0].b);
    expect(0, y[0].x[1].a);
    expect(0, y[0].x[1].b);
    expect(0, y[0].x[2].a);
    expect(10, y[0].x[2].b);
    expect(11, y[1].x[0].a);
    expect(5, y[1].x[0].b);
    expect(6, y[1].x[1].a);
    expect(7, y[1].x[1].b);
    expect(8, y[1].x[2].a);
    expect(9, y[1].x[2].b);

    int y2[][3] = { [0][0] = 1, [1][0] = 3 };
    expect(1, y2[0][0]);
    expect(3, y2[1][0]);

    struct { int a, b[3]; } y3 = { .a = 1, .b[0] = 10, .b[1] = 11 };
    expect(1, y3.a);
    expect(10, y3.b[0]);
    expect(11, y3.b[1]);
    expect(0, y3.b[2]);
}