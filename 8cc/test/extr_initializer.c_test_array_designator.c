__attribute__((used)) static void test_array_designator() {
    int v[3] = { [1] = 5 };
    expect(0, v[0]);
    expect(5, v[1]);
    expect(0, v[2]);

    struct { int a, b; } x[2] = { [1] = { 1, 2 } };
    expect(0, x[0].a);
    expect(0, x[0].b);
    expect(1, x[1].a);
    expect(2, x[1].b);

    struct { int a, b; } x2[3] = { [1] = 1, 2, 3, 4 };
    expect(0, x2[0].a);
    expect(0, x2[0].b);
    expect(1, x2[1].a);
    expect(2, x2[1].b);
    expect(3, x2[2].a);
    expect(4, x2[2].b);

    int x3[] = { [2] = 3, [0] = 1, 2 };
    expect(1, x3[0]);
    expect(2, x3[1]);
    expect(3, x3[2]);
}